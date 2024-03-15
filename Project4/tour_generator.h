#ifndef TOURGENERATOR_H
#define TOURGENERATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "base_classes.h"
#include "tourcmd.h"
#include "geotools.h"

class TourGenerator : public TourGeneratorBase
{
public:
	TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
	virtual ~TourGenerator();
	virtual std::vector<TourCommand> generate_tour(const Stops& stops) const; // generates a list of commands for the tour
private:
	const GeoDatabaseBase& gdb;
	const RouterBase& rtr;
	std::string direction(const GeoPoint& pt1, const GeoPoint& pt2) const;
};

#endif // TOURGENERATOR_H
