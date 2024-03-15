#include "geodb.h"

GeoDatabase::GeoDatabase()
{}

GeoDatabase::~GeoDatabase()
{}

bool GeoDatabase::load(const std::string& map_data_file)
{
	// mapdata.txt: shows all streets
	// stops.txt: shows all stops

	std::ifstream infile(map_data_file); // get file
	if (!infile) // if file does not exist, return false
	{
		return false;
	}

	string line;
	string streetName;
	string slat;
	string slong;
	string elat;
	string elong;
	string sgp;
	string egp;
	string segment;
	string stops;
	int numStops;

	while (getline(infile, streetName))
	{
		getline(infile, line); // get line with GeoPoints
		istringstream iss_points(line);
		iss_points >> slat >> slong >> elat >> elong; // separate into individual strings
		GeoPoint start = GeoPoint(slat, slong); // create starting GeoPoint
		GeoPoint end = GeoPoint(elat, elong); // create ending GeoPoint
		segment = convertToSegment(start, end); // convert GeoPoints into a segment string
		m_streets.insert(segment, streetName); // insert into street hashmap

		getline(infile, line); // get line with the number of stops
		istringstream iss_num_spots(line);
		iss_num_spots >> numStops; // insert the number of stops
		vector<GeoPoint>* scpPtr = m_connected_points.find(start.to_string()); // get the connecting points of the start
		if (scpPtr != nullptr) // if connecting points already exist, push back the end
		{
			(*scpPtr).push_back(end);
		}
		else // connecting points do not exist
		{
			vector<GeoPoint> sgpv; // create new vector
			sgpv.push_back(end); // push item into new vector
			m_connected_points.insert(start.to_string(), sgpv); // insert new vector
		}
		std::vector<GeoPoint>* ecpPtr = m_connected_points.find(end.to_string()); // get connecting points of the end
		if (ecpPtr != nullptr)
		{
			(*ecpPtr).push_back(start);
		}
		else
		{
			vector<GeoPoint> egpv;
			egpv.push_back(start);
			m_connected_points.insert(end.to_string(), egpv);
		}
		if (numStops != 0)
		{
			std::vector<GeoPoint>* start_connected = m_connected_points.find(start.to_string()); // start connected vector
			std::vector<GeoPoint>* end_connected = m_connected_points.find(end.to_string()); // end connected vector

			GeoPoint mid = midpoint(start, end); // compute the midpoint;

			(*start_connected).push_back(mid); // push back mid to both end and start
			(*end_connected).push_back(mid);

			std::vector<GeoPoint> mid_connected; // create mid connected vector
			mid_connected.push_back(start);
			mid_connected.push_back(end);

			std::string start_mid_segment = convertToSegment(start, mid);
			std::string end_mid_segment = convertToSegment(mid, end);

			m_streets.insert(start_mid_segment, streetName); // make start to mid and end to mid part of a street
			m_streets.insert(end_mid_segment, streetName);

			for (int i = 0; i < numStops; i++)
			{
				std::string stopName; // extract information on stop from file
				std::string stopGP;
				getline(infile, line);
				istringstream stopLine(line);
				getline(stopLine, stopName, '|');
				getline(stopLine, stopGP);
				istringstream stoplatlong(stopGP);
				std::string stoplat;
				std::string stoplong;
				stoplatlong >> stoplat >> stoplong;
				
				GeoPoint stop(stoplat, stoplong);

				mid_connected.push_back(stop); // connect mid to stop

				std::vector<GeoPoint> stop_connected;
				stop_connected.push_back(mid); // connect stop to mid, mid is the only item
				m_connected_points.insert(stop.to_string(), stop_connected);

				std::string mid_stop_segment = convertToSegment(mid, stop);
				m_streets.insert(mid_stop_segment, "a path");

				m_poi_locations.insert(stopName, stop); // insert into POI hashmap
			}
			m_connected_points.insert(mid.to_string(), mid_connected);
		}
	}
	return true;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const
{
	const GeoPoint* poipt = m_poi_locations.find(poi);
	if (poipt != nullptr)
	{
		point = *poipt;
		return true;
	}
	return false;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const
{
	string stringpt = pt.to_string();
	const std::vector<GeoPoint>* g = m_connected_points.find(stringpt);
	if (g == nullptr)
	{
		std::vector<GeoPoint> s;
		return s;
	}
	vector<GeoPoint> connected(g->size());
	for (int i = 0; i < g->size(); i++)
	{
		connected[i] = (*g)[i];
	}
	return connected;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	string segment1 = convertToSegment(pt1, pt2);
	string segment2 = convertToSegment(pt2, pt1);
	string street = "";
	const std::string* streetPtr1 = m_streets.find(segment1);
	const std::string* streetPtr2 = m_streets.find(segment2);
	if (streetPtr1 != nullptr)
	{
		street = *streetPtr1;
	}
	else if (streetPtr2 != nullptr)
	{
		street = *streetPtr2;
	}
	return street;
}

std::string GeoDatabase::convertToSegment(const GeoPoint& s, const GeoPoint& e) const
{
	return (s.sLatitude + ',' + s.sLongitude + ' ' + e.sLatitude + ',' + e.sLongitude);
}

