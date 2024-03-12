#include "router.h"

Router::Router(const GeoDatabaseBase& geo_db)
	: gdb(geo_db)
{}

Router::~Router()
{}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	HashMap<GeoPoint> parent;
	std::priority_queue<vertex, std::vector<vertex>, compVertex> nextVertex;
	std::set<vertex> visiting;
	std::set<vertex> visited;
	std::vector<GeoPoint> path;

	vertex s = vertex(pt1, pt1, pt2);
	vertex e = vertex(pt1, pt2, pt2);
	if (s.fs == 0) // start is already at the end
	{
		std::cerr << "START IS END" << endl;
		return path;
	}
	nextVertex.push(s);
	visiting.insert(s);

	while (!visiting.empty())
	{
		vertex curr = nextVertex.top();
		nextVertex.pop();
		visiting.erase(curr);
		visited.insert(curr);

		if (curr.fs == 0)
		{
			std::cout << "PATH IS FOUND" << endl;
			path.clear();
			GeoPoint currGP = curr.getGeoPoint();
			std::cout << currGP.to_string() << " " << pt1.to_string() << endl;
			std::cout << e.getGeoPoint().to_string() << endl;
			int i = 0;
			while (i < 10)
			{
				std::cout << "ADDING TO PATH: " << currGP.to_string() << endl;
				path.push_back(currGP);
				currGP = parent[currGP.to_string()];
				i++;
			}
			path.push_back(currGP);
			std::reverse(path.begin(), path.end());
			return path;
		}
		else
		{
			std::cout << "PATH NOT FOUND YET" << endl;
		}

		std::vector<GeoPoint> adjGP = gdb.get_connected_points(curr.getGeoPoint());
		for (int i = 0; i < adjGP.size(); i++)
		{
			vertex adjVertex = vertex(curr.getGeoPoint(), adjGP[i], pt2);
			if (visited.find(adjVertex) != visited.end())
			{
				std::cout << "ALREADY VISITED: " << adjVertex.getGeoPoint().to_string() << endl;
				continue;
			}
			std::set<vertex>::iterator ptr = visiting.find(adjVertex);
			if (ptr != visiting.end())
			{
				if (adjVertex.gs > (*ptr).gs)
				{
					std::cout << "VISITING HAS A BETTER PATH" << endl;
					continue;
				}
			}
			parent.insert(adjVertex.getGeoPoint().to_string(), curr.getGeoPoint());
			std::cout << "INSERTING parent[" << adjGP[i].to_string() << "] = " << curr.getGeoPoint().to_string() << endl;
			nextVertex.push(adjVertex);
			visiting.insert(adjVertex);
		}
	}
	std::cerr << "SHOULD NEVER REACH HERE" << endl;
	return path;
}