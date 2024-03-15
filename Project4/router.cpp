#include "router.h"

Router::Router(const GeoDatabaseBase& geo_db)
	: gdb(geo_db)
{}

Router::~Router()
{}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	std::vector<GeoPoint> path; // vector of path
	std::priority_queue<Vertex*, std::vector<Vertex*>, compareVertex> nextVertex; // outputs the vertex with the lowest f score
	std::unordered_set<Vertex, VertexHash, VertexEqual> openList; // vertices to be considered
	std::unordered_set<Vertex, VertexHash, VertexEqual> closedList; // visited vertices
	HashMap<GeoPoint> parent;
	Vertex* start = new Vertex(0, distance_earth_km(pt1, pt2), pt1); // starting vertex

	if (start->fs == 0) // start is the same point as the end
	{
		path.push_back(pt1);
		delete start;
		start = nullptr;
		return path;
	}

	nextVertex.push(start); // push vertex into the next
	openList.insert(*start);

	while (!openList.empty())
	{
		Vertex* current = nextVertex.top(); // vertex with the lowest f score
		openList.erase(*current);
		nextVertex.pop();

		std::vector<GeoPoint> adjacentGP = gdb.get_connected_points(current->gp); // get all adjacent vertices
		for (int i = 0; i < adjacentGP.size(); i++)
		{
			if (parent.find(adjacentGP[i].to_string()) == nullptr) // if vertex does not have an assigned parent, insert parent
				parent.insert(adjacentGP[i].to_string(), current->gp);
			if ((adjacentGP[i].latitude == pt2.latitude) && (adjacentGP[i].longitude == pt2.longitude)) // adjacent vertex is the end vertex
			{
				GeoPoint pathGP = adjacentGP[i];
				while (!((pathGP.latitude == pt1.latitude) && (pathGP.longitude == pt1.longitude)))
				{
					path.push_back(pathGP);
					pathGP = parent[pathGP.to_string()];
				}
				path.push_back(pathGP);
				std::reverse(path.begin(), path.end());

				delete current;
				current = nullptr;
				while (!nextVertex.empty())
				{
					Vertex* toBeDeleted = nextVertex.top();
					delete toBeDeleted;
					toBeDeleted = nullptr;
					nextVertex.pop();
				}

				return path;
			}
			Vertex* adjacentVertex = new Vertex(current->gs + distance_earth_km(current->gp, adjacentGP[i]), distance_earth_km(adjacentGP[i], pt2), adjacentGP[i]); // create new vertex for the adjacent nodes 
			std::unordered_set<Vertex>::iterator findInOL = openList.find(*adjacentVertex);
			if (findInOL != openList.end()) // vertex has already been considered
			{
				if ((*findInOL).fs < adjacentVertex->fs)
				{
					delete adjacentVertex; // delete unoptimal vertex
					adjacentVertex = nullptr;
					continue;
				}
				parent.insert(adjacentGP[i].to_string(), current->gp);
			}
			std::unordered_set<Vertex>::iterator findInCL = closedList.find(*adjacentVertex);
			if (findInCL != closedList.end()) // vertex has already been visited
			{
				if ((*findInCL).fs < adjacentVertex->fs)
				{
					delete adjacentVertex; // delete unoptimal vertex
					adjacentVertex = nullptr;
					continue;
				}
			}
			nextVertex.push(adjacentVertex); // push the vertex into the priority queue
			openList.insert(*adjacentVertex);
		}
		closedList.insert(*current); // insert the current vertex to the closed list
		delete current;
	}
	// path was not found
	while (!nextVertex.empty())
	{
		Vertex* toBeDeleted = nextVertex.top();
		delete toBeDeleted;
		toBeDeleted = nullptr;
		nextVertex.pop();
	}
	return path;
}

// Vertex Implementation

Vertex::Vertex(double g, double h, GeoPoint pt)
	: gs(g), hs(h), fs(g + h), gp(pt)
{}

bool Vertex::operator==(const Vertex& other)
{
	return ((gp.latitude == other.gp.latitude) && (gp.longitude == other.gp.longitude));
}

bool compareVertex::operator()(const Vertex* vl, const Vertex* vr)
{
	if (vl->fs > vr->fs)
		return true;
	if (vl->fs < vr->fs)
		return false;
	return false;
}