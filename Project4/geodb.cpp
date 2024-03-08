#include "geodb.h"

GeoDatabase::GeoDatabase()
{}

GeoDatabase::~GeoDatabase()
{}

bool GeoDatabase::load(const std::string& map_data_file)
{
	// mapdata.txt: shows all streets
	// stops.txt: shows all stops

	std::ifstream infile(map_data_file);
	if (!infile)
	{
		return false;
	}
	
	std::string line;
	while (getline(infile, line))
	{
		std::vector<Segment> street;

		std::istringstream iss(line);
		std::string streetName;
		std::string segmentValues[4];
		int numSpots;
		if (iss >> streetName)
		{
			if (getline(infile, line))
			{
				std::string latlong;
				for (int i = 0; i < 4 && iss >> latlong; i++)
				{
					segmentValues[i] = latlong;
				}

				if (getline(infile, line))
				{
					if (iss >> numSpots)
					{
						if (numSpots == 0)
						{
							Segment s = Segment(GeoPoint(segmentValues[0], segmentValues[1]), GeoPoint(segmentValues[2], segmentValues[3]));
							street.push_back(s);
							m_map.insert(streetName, street);
						}
					}
				}
			}
		}
	}
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const
{

}

