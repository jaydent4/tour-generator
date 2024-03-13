#include "router.h"

Router::Router(const GeoDatabaseBase& geo_db)
	: gdb(geo_db)
{}

Router::~Router()
{}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	std::vector<GeoPoint> path;
	HashMap<GeoPoint> parent;
	std::priority_queue<vertex, std::vector<vertex>, compVertex> nextVertex;
	HashMap<bool> visited;

	vertex start = vertex(0, pt1, pt2);
	vertex end = vertex(999, pt2, pt2);

	if (start.fs == 0) // start is the same GeoPoint as the end
	{
		return path;
	}

	nextVertex.push(start);
	visited.insert(start.getGeoPoint().to_string(), true);

	while (!nextVertex.empty())
	{
		std::priority_queue<vertex, std::vector<vertex>, compVertex> copy(nextVertex);
		std::cout << copy.size() << " | ";
		for (int i = 0; i <= copy.size(); i++)
		{
			std::cout << copy.top().getGeoPoint().to_string() << " | ";
			copy.pop();
		}
		std::cout << endl;

		vertex current = nextVertex.top();
		nextVertex.pop();
		std::cout << "CURRENT VERTEX VALUES: gs = " << current.gs << "    hs = " << current.hs << endl;

		GeoPoint currGP = current.getGeoPoint();
		std::cout << "CURRENT GP: " << currGP.to_string() << endl;

		if (current.hs == 0)
		{
			std::cout << "PATH FOUND" << endl;
			return path;
		}

		std::vector<GeoPoint> adjGP = gdb.get_connected_points(current.getGeoPoint());
		for (int i = 0; i < adjGP.size(); i++)
		{
			std::cout << "ADJACENT IS: " << adjGP[i].to_string() << endl;
			if (visited[adjGP[i].to_string()] == false)
			{
				double currToAdjDistance = distance_earth_km(currGP, adjGP[i]);
				vertex adj(current.gs + currToAdjDistance, adjGP[i], pt2);
				visited.insert(adj.getGeoPoint().to_string(), true);
				std::cout << adjGP[i].to_string() << " has not been visited" << endl;
				std::cout << "Pushing " << adj.getGeoPoint().to_string() << " onto priority queue" << endl;
				nextVertex.push(adj);
				parent.insert(adjGP[i].to_string(), currGP);

				std::priority_queue<vertex, std::vector<vertex>, compVertex> copy(nextVertex);
				std::cout << "nextVertex is now: " << copy.size() << " | ";
				for (int i = 0; i <= copy.size(); i++)
				{
					std::cout << copy.top().getGeoPoint().to_string() << " | ";
					copy.pop();
				}
				std::cout << endl;
			}
			else
				std::cout << adjGP[i].to_string() << " has already been visited" << endl;
		}
	}
	std::cout << "ENDING EARLY OR NO SOLUTION" << endl;
	return path;
}