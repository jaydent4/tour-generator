#ifndef GEODATABASE_H
#define GEODATABASE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "base_classes.h"
#include "HashMap.h"

class GeoDatabase : public GeoDatabaseBase
{
public:
	GeoDatabase();
	virtual ~GeoDatabase();
	virtual bool load(const std::string& map_data_file);
	virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
	virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	struct Segment
	{
		Segment(GeoPoint s, GeoPoint e)
		{
			start = s;
			end = e;
			m_numStops = 0;
		}
		GeoPoint start;
		GeoPoint end;
		int m_numStops;
	};
	HashMap<std::vector<Segment>> m_map;
};


#endif // GEODATABASE_H