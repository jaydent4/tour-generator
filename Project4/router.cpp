#include "router.h"

Router::Router(const GeoDatabaseBase& geo_db)
	: gdb(geo_db)
{}

Router::~Router()
{}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	std::vector<GeoPoint> path;
	std::priority_queue<Vertex*, std::vector<Vertex*>, compareVertex> nextVertex;
	std::unordered_set<Vertex, VertexHash, VertexEqual> openList;
	std::unordered_set<Vertex, VertexHash, VertexEqual> closedList;
	HashMap<GeoPoint> parent;
	Vertex* start = new Vertex(0, distance_earth_km(pt1, pt2), pt1);

	if (start->fs == 0)
	{
		path.push_back(pt1);
		delete start;
		start = nullptr;
		return path;
	}

	nextVertex.push(start);
	openList.insert(*start);

	while (!openList.empty())
	{
		Vertex* current = nextVertex.top();
		openList.erase(*current);
		nextVertex.pop();

		std::vector<GeoPoint> adjacentGP = gdb.get_connected_points(current->gp);
		for (int i = 0; i < adjacentGP.size(); i++)
		{
			if (parent.find(adjacentGP[i].to_string()) == nullptr)
				parent.insert(adjacentGP[i].to_string(), current->gp);
			if ((adjacentGP[i].latitude == pt2.latitude) && (adjacentGP[i].longitude == pt2.longitude))
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
			Vertex* adjacentVertex = new Vertex(current->gs + distance_earth_km(current->gp, adjacentGP[i]), distance_earth_km(adjacentGP[i], pt2), adjacentGP[i]);
			std::unordered_set<Vertex>::iterator findInOL = openList.find(*adjacentVertex);
			if (findInOL != openList.end())
			{
				if ((*findInOL).fs < adjacentVertex->fs)
				{
					delete adjacentVertex;
					adjacentVertex = nullptr;
					continue;
				}
				parent.insert(adjacentGP[i].to_string(), current->gp);
			}
			std::unordered_set<Vertex>::iterator findInCL = closedList.find(*adjacentVertex);
			if (findInCL != closedList.end())
			{
				if ((*findInCL).fs < adjacentVertex->fs)
				{
					delete adjacentVertex;
					adjacentVertex = nullptr;
					continue;
				}
			}
			nextVertex.push(adjacentVertex);
			openList.insert(*adjacentVertex);
		}
		closedList.insert(*current);
	}
	while (!nextVertex.empty())
	{
		Vertex* toBeDeleted = nextVertex.top();
		delete toBeDeleted;
		toBeDeleted = nullptr;
		nextVertex.pop();
	}
	return path;
}