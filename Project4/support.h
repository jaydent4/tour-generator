#ifndef SUPPORT_H
#define SUPPORT_H

#include "geopoint.h"
#include "geotools.h"

struct vertex
{
	vertex(GeoPoint start, GeoPoint current, GeoPoint end)
		: gp(current)
	{
		gs = distance_earth_km(start, current); // Distance from start to current
		hs = distance_earth_km(current, end); // Distance from current to end
		fs = gs + hs; // cost of traversing to a vertext
	}
	const GeoPoint gp;
	double gs;
	double hs;
	double fs;
	bool operator>(const vertex& other) const;
	bool operator<(const vertex& other) const;
	bool operator==(const vertex& other) const;
	void operator=(const vertex& other);
	const GeoPoint& getGeoPoint() const;
};

struct compVertex
{
	bool operator()(const vertex& vl, const vertex& vr) const
	{
		return (vl.fs > vr.fs);
	}
};

#endif // SUPPORT_H