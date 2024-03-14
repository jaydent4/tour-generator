#include "router.h"

Router::Router(const GeoDatabaseBase& geo_db)
	: gdb(geo_db)
{}

Router::~Router()
{}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	std::priority_queue<Vertex*, std::vector<Vertex*>, compareVertex> testVertex;
	GeoPoint first = GeoPoint("1", "1");
	GeoPoint second = GeoPoint("1", "6");
	GeoPoint third = GeoPoint("2", "8");
	GeoPoint last = GeoPoint("7", "7");
	Vertex* ptr1 = new Vertex(0, distance_earth_km(first, last), first);
	testVertex.push(ptr1);
	Vertex* ptr2 = new Vertex(ptr1->hs + distance_earth_km(first, second), distance_earth_km(second, last), second);
	testVertex.push(ptr2);
	Vertex* ptr3 = new Vertex(ptr2->hs + distance_earth_km(second, third), distance_earth_km(third, last), third);
	testVertex.push(ptr3);

	while (!testVertex.empty())
	{
		Vertex* ptr = testVertex.top();
		std::cout << ptr->gp.to_string() << endl;
		delete ptr;
		testVertex.pop();
	}

	std::vector<GeoPoint> temp;
	return temp;

	//std::priority_queue<vertex, std::vector<vertex>, compVertex> testVertex;
	//vertex first = vertex(0, pt1, pt2);
	//std::cout << "first: " << first.getGeoPoint().to_string() << endl;

	//GeoPoint secondGP = GeoPoint("1", "5");
	//vertex second = vertex(first.gs + distance_earth_km(secondGP, pt1), secondGP, pt2);
	//std::cout << "second: " << second.getGeoPoint().to_string() << endl;

	//GeoPoint thirdGP = GeoPoint("2", "8");
	//vertex third = vertex(second.gs + distance_earth_km(thirdGP, secondGP), thirdGP, pt2);
	//std::cout << "third: " << third.getGeoPoint().to_string() << endl;

	//testVertex.push(first);
	//testVertex.push(second);
	//testVertex.push(third);
	//std::cout << "testVertex: " << endl;
	//while (!testVertex.empty())
	//{
	//	std::cout << testVertex.top().getGeoPoint().to_string() << endl;
	//	testVertex.pop();
	//}

	//std::vector<GeoPoint> temp;
	//return temp;

	//std::set<vertex> openList;
	//std::set<vertex> closedList;
	//std::priority_queue<vertex, std::vector<vertex>, compVertex> nextVertex;
	//std::vector<GeoPoint> path;
	//HashMap<GeoPoint> parent;

	//vertex start(0, pt1, pt2);
	//vertex end(999, pt2, pt2);

	//if (start == end)
	//{
	//	return path; // start is the end
	//}

	//openList.insert(start); // insert the start into open list
	//nextVertex.push(start);

	//while (!openList.empty())
	//{
	//	vertex current = nextVertex.top();
	//	std::cout << "CURRENT IS NOW: " << current.getGeoPoint().to_string() << endl;
	//	std::priority_queue<vertex, std::vector<vertex>, compVertex> copy(nextVertex);
	//	std::cout << copy.size() << " | ";
	//	for (int i = 0; i <= copy.size(); i++)
	//	{
	//		std::cout << copy.top().getGeoPoint().to_string() << " | ";
	//		copy.pop();
	//	}
	//	std::cout << endl;
	//	nextVertex.pop();
	//	openList.erase(current);
	//	std::cout << "OPEN LIST SIZE: " << openList.size() << endl;

	//	std::vector<GeoPoint> adjacentGP = gdb.get_connected_points(current.getGeoPoint());
	//	for (int i = 0; i < adjacentGP.size(); i++)
	//	{
	//		std::cout << "CHECKING ADJACENT: " << adjacentGP[i].to_string() << endl;
	//		parent.insert(adjacentGP[i].to_string(), current.getGeoPoint()); // set all of the parents
	//		vertex adjacent(current.gs + distance_earth_km(current.getGeoPoint(), adjacentGP[i]), adjacentGP[i], pt2); // initialize new vertex for the adjacent node

	//		if (adjacent == end)
	//		{
	//			std::cout << "PATH FOUND" << endl;
	//			return path;
	//		}

	//		std::set<vertex>::iterator vertexInOL = openList.find(adjacent); // check if the node on the open list is better than the current one
	//		if (vertexInOL != openList.end())
	//		{
	//			std::cout << "ADJACENT IS ALREADY IN OPEN LIST" << endl;
	//			if ((*vertexInOL).fs < adjacent.fs)
	//			{
	//				std::cout << adjacent.getGeoPoint().to_string() << ": F SCORE IS BIGGER THAN THE ONE IN OPEN LIST" << endl;
	//				continue;
	//			}
	//		}
	//		
	//		std::set<vertex>::iterator vertexInCL = closedList.find(adjacent); // check if the node is on the closed list
	//		if (vertexInCL != closedList.end())
	//		{
	//			std::cout << "ADJACENT IS ALREADY IN CLOSED LIST" << endl;
	//			if ((*vertexInCL).fs < adjacent.fs)
	//			{
	//				std::cout << adjacent.getGeoPoint().to_string() << ": F SCORE IS BIGGER THAN THE ONE IN CLOSED LIST" << endl;
	//				continue;
	//			}
	//		}
	//		std::cout << adjacent.getGeoPoint().to_string() << " is being added to openList" << endl;
	//		nextVertex.push(adjacent);
	//		openList.insert(adjacent);
	//	}
	//	closedList.insert(current);
	//	std::cout << current.getGeoPoint().to_string() << " is being added to closedList" << endl;
	//}
	//std::cout << "SHOULD NEVER GET HERE" << endl;
	//return path;


	//std::vector<GeoPoint> path;
	//HashMap<GeoPoint> parent;
	//std::priority_queue<vertex, std::vector<vertex>, compVertex> nextVertex;
	//HashMap<bool> visited;

	//vertex start = vertex(0, pt1, pt2);
	//vertex end = vertex(999, pt2, pt2);

	//if (start.fs == 0) // start is the same GeoPoint as the end
	//{
	//	return path;
	//}

	//nextVertex.push(start);
	//visited.insert(start.getGeoPoint().to_string(), true);

	//while (!nextVertex.empty())
	//{
	//	std::priority_queue<vertex, std::vector<vertex>, compVertex> copy(nextVertex);
	//	std::cout << copy.size() << " | ";
	//	while (!copy.empty())
	//	{
	//		std::cout << copy.top().getGeoPoint().to_string() << " | ";
	//		copy.pop();
	//	}
	//	std::cout << endl;

	//	vertex current = nextVertex.top();
	//	nextVertex.pop();
	//	std::cout << "CURRENT VERTEX VALUES: gs = " << current.gs << "    hs = " << current.hs << endl;

	//	GeoPoint currGP = current.getGeoPoint();
	//	std::cout << "CURRENT GP: " << currGP.to_string() << endl;

	//	if (current.hs == 0)
	//	{
	//		std::cout << "PATH FOUND" << endl;
	//		return path;
	//	}

	//	std::vector<GeoPoint> adjGP = gdb.get_connected_points(current.getGeoPoint());
	//	for (int i = 0; i < adjGP.size(); i++)
	//	{
	//		std::cout << "ADJACENT IS: " << adjGP[i].to_string() << endl;
	//		if (visited[adjGP[i].to_string()] == false)
	//		{
	//			double currToAdjDistance = distance_earth_km(currGP, adjGP[i]);
	//			vertex adj(current.gs + currToAdjDistance, adjGP[i], pt2);
	//			visited.insert(adj.getGeoPoint().to_string(), true);
	//			std::cout << adjGP[i].to_string() << " has not been visited" << endl;
	//			std::cout << "Pushing " << adj.getGeoPoint().to_string() << " onto priority queue" << endl;

	//			std::priority_queue<vertex, std::vector<vertex>, compVertex> bcopy(nextVertex);
	//			std::cout << "nextVertex before push is: " << bcopy.size() << " | ";
	//			while (!bcopy.empty())
	//			{
	//				std::cout << bcopy.top().getGeoPoint().to_string() << " | ";
	//				bcopy.pop();
	//			}
	//			std::cout << endl;

	//			nextVertex.push(adj);
	//			parent.insert(adjGP[i].to_string(), currGP);

	//			std::priority_queue<vertex, std::vector<vertex>, compVertex> copy(nextVertex);
	//			std::cout << "nextVertex after push is: " << copy.size() << " | ";
	//			while (!copy.empty())
	//			{
	//				std::cout << copy.top().getGeoPoint().to_string() << " | ";
	//				copy.pop();
	//			}
	//			std::cout << endl;
	//		}
	//		else
	//			std::cout << adjGP[i].to_string() << " has already been visited" << endl;
	//	}
	//}
	//std::cout << "ENDING EARLY OR NO SOLUTION" << endl;
	//return path;
}