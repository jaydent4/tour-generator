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
		getline(infile, line);
		istringstream iss_points(line);
		iss_points >> slat >> slong >> elat >> elong;
		sgp = slat + "," + slong;
		egp = elat + "," + elong;
		segment = convertToSegment(GeoPoint(slat, slong), GeoPoint(elat, elong));
		getline(infile, line);
		istringstream iss_num_spots(line);
		iss_num_spots >> numStops;
		m_streets.insert(segment, streetName); // insert into street hashmap
		vector<GeoPoint>* scpPtr = m_connected_points.find(sgp);
		if (scpPtr != nullptr)
		{
			(*scpPtr).push_back(GeoPoint(elat, elong));
		}
		else
		{
			vector<GeoPoint> sgpv;
			sgpv.push_back(GeoPoint(elat, elong));
			m_connected_points.insert(sgp, sgpv);
		}
		std::vector<GeoPoint>* ecpPtr = m_connected_points.find(egp);
		if (ecpPtr != nullptr)
		{
			(*ecpPtr).push_back(GeoPoint(slat, slong));
		}
		else
		{
			vector<GeoPoint> egpv;
			egpv.push_back(GeoPoint(slat, slong));
			m_connected_points.insert(egp, egpv);
		}
		if (numStops != 0)
		{
			vector<GeoPoint>* nscpPtr = m_connected_points.find(sgp);
			std::vector<GeoPoint>* necpPtr = m_connected_points.find(egp);
			GeoPoint spt = GeoPoint(slat, slong);
			GeoPoint ept = GeoPoint(elat, elong);
			GeoPoint mid = midpoint(spt, ept);
			string stringMid = mid.to_string();
			for (int i = 0; i < numStops; i++)
			{
				string stName;
				string stgp;
				string stlat;
				string stlong;
				string stopgp = stlat + ',' + stlong;
				string stSegment;
				string sptmidSegment = convertToSegment(spt, mid);
				string eptmidSegment = convertToSegment(ept, mid);

				getline(infile, line);
				istringstream stopLine(line);
				getline(stopLine, stName, '|');
				getline(stopLine, stgp);
				istringstream stoplatlong(stgp);
				stoplatlong >> stlat >> stlong;
				stSegment = convertToSegment(mid, GeoPoint(stlat, stlong));
				m_streets.insert(stSegment, "a path");
				m_streets.insert(sptmidSegment, streetName);
				m_streets.insert(eptmidSegment, streetName);
				m_poi_locations.insert(stName, GeoPoint(stlat, stlong));

				// Connected Points
				(*nscpPtr).push_back(mid); // add midpoint to segment begin and end
				(*necpPtr).push_back(mid);

				vector<GeoPoint> stop;
				stop.push_back(mid);
				m_connected_points.insert(stopgp, stop);

				std::vector<GeoPoint>* mgpv = m_connected_points.find(stringMid);
				if (mgpv == nullptr)
				{
					vector<GeoPoint> connected_mid;
					connected_mid.push_back(spt); // start point
					connected_mid.push_back(ept); // end point
					connected_mid.push_back(GeoPoint(stlat, stlong)); // stop point
					m_connected_points.insert(stringMid, connected_mid);
				}
				else
				{
					(*mgpv).push_back(GeoPoint(stlat, stlong)); // insert new stop if mid already exists
				}
			}
		}
	}
	return true;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const
{
	GeoPoint* poipt = m_poi_locations.find(poi);
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
	std::vector<GeoPoint>* g = m_connected_points.find(stringpt);
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
	std::string* streetPtr1 = m_streets.find(segment1);
	std::string* streetPtr2 = m_streets.find(segment2);
	if (streetPtr1 != nullptr)
	{
		// street = m_streets[segment1];
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

