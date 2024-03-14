#ifndef SUPPORT_H
#define SUPPORT_H

#include "geopoint.h"
#include "geotools.h"

struct Vertex
{
	Vertex(double g, double h, GeoPoint pt);
	double gs;
	double hs;
	double fs;
	GeoPoint gp;
};

struct compareVertex
{
	bool operator()(const Vertex* vl, const Vertex* vr);
};

//struct vertex
//{
//	vertex(double newgs, GeoPoint current, GeoPoint end)
//		: gp(current)
//	{
//		gs = newgs; // Distance from current to next
//		hs = distance_earth_km(current, end); // Distance from current to end
//		fs = gs + hs; // cost of traversing to a vertext
//	}
//	vertex(const vertex& other);
//	GeoPoint gp;
//	double gs;
//	double hs;
//	double fs;
//	bool operator>(const vertex& other) const;
//	bool operator<(const vertex& other) const;
//	bool operator==(const vertex& other) const;
//	void operator=(const vertex& other);
//	const GeoPoint& getGeoPoint() const;
//};
//
//struct compVertex
//{
//	bool operator()(const vertex& vl, const vertex& vr) const
//	{
//		return (vl > vr);
//	}
//};

#endif // SUPPORT_H