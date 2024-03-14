#include "tour_generator.h"

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router)
	: gdb(geodb), rtr(router)
{}

TourGenerator::~TourGenerator()
{}

std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const
{
	std::vector<TourCommand> result;
	std::vector<TourCommand> empty;

	if (stops.size() == 0)
		return result;

	std::string stopName;
	std::string commentary;
	if (stops.get_poi_data(0, stopName, commentary))
	{
		TourCommand instruction = TourCommand();
		instruction.init_commentary(stopName, commentary);
		result.push_back(instruction);
	}
	else
	{
		return empty;
	}

	std::string prevPOI = stopName;
	GeoPoint prevGP;
	if (!gdb.get_poi_location(prevPOI, prevGP))
	{
		return empty;
	}


	for (int i = 1; i < stops.size(); i++)
	{
		std::string currPOI;
		if (stops.get_poi_data(i, currPOI, commentary))
		{
			GeoPoint currGP;
			if (gdb.get_poi_location(currPOI, currGP))
			{
				std::vector<GeoPoint> path = rtr.route(prevGP, currGP);

				if (path.empty())
					return empty;

				if (path.size() == 1)
				{
					TourCommand cmty;
					cmty.init_commentary(currPOI, commentary);
					result.push_back(cmty);
					continue;
				}

				for (int i = 0; i < path.size() - 1; i++)
				{

					std::string streetName = gdb.get_street_name(path[i], path[i + 1]);
					std::string dir = direction(path[i], path[i + 1]);
					double dist = distance_earth_miles(path[i], path[i + 1]);

					TourCommand proceed;
					proceed.init_proceed(dir, streetName, dist, path[i], path[i + 1]);
					result.push_back(proceed);

					if (i < path.size() - 2 && gdb.get_street_name(path[i], path[i + 1]) != gdb.get_street_name(path[i + 1], path[i + 2]) && angle_of_turn(path[i], path[i + 1], path[i + 2]) >= 1 && angle_of_turn(path[i], path[i + 1], path[i + 2]) <= 359)
					{
						std::string streetName = gdb.get_street_name(path[i + 1], path[i + 2]);
						std::string turndir;
						if (angle_of_turn(path[i], path[i + 1], path[i + 2]) < 180)
							turndir = "left";
						else if (angle_of_turn(path[i], path[i + 1], path[i + 2]) <= 359)
							turndir = "right";

						TourCommand turn;
						turn.init_turn(turndir, streetName);
						result.push_back(turn);
					}
				}
				TourCommand cmty;
				cmty.init_commentary(currPOI, commentary);
				result.push_back(cmty);
			}
			else
			{
				return empty;
			}
			prevGP = currGP;
			prevPOI = currPOI;
		}
		else
		{
			return empty;
		}
	}
	return result;
}

std::string TourGenerator::direction(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	double angle = angle_of_line(pt1, pt2);
	if ((0 <= angle && angle < 22.5) || (angle >= 337.5))
		return "east";
	else if (22.5 <= angle && angle < 67.5)
		return "northeast";
	else if (67.5 <= angle && angle < 112.5)
		return "north";
	else if (112.5 <= angle && angle < 157.5)
		return "northwest";
	else if (157.5 <= angle && angle < 202.5)
		return "west";
	else if (202.5 <= angle && angle < 247.5)
		return "southwest";
	else if (247.5 <= angle && angle < 292.5)
		return "south";
	else if (292.5 <= angle && angle < 337.5)
		return "southeast";
	return "BAD ANGLE";
}