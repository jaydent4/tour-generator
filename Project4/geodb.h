#ifndef GEODATABASE_H
#define GEODATABASE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "base_classes.h"
#include "hashmap.h"
#include "geotools.h"

class GeoDatabase : public GeoDatabaseBase
{
public:
	GeoDatabase();
	virtual ~GeoDatabase();
	virtual bool load(const std::string& map_data_file);
	virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
	virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
	virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	HashMap<GeoPoint> m_poi_locations;
	HashMap<std::vector<GeoPoint>> m_connected_points;
	HashMap<std::string> m_streets;
	string convertToSegment(const GeoPoint& s, const GeoPoint& e) const;
};


#endif // GEODATABASE_H