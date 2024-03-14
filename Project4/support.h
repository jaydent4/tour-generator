#ifndef SUPPORT_H
#define SUPPORT_H

#include "geopoint.h"
#include "geotools.h"
#include <string>

struct Vertex
{
	Vertex(double g, double h, GeoPoint pt);
	double gs; // distance of path
	double hs; // distance from end
	double fs; // gs + hs
	GeoPoint gp;
	bool operator==(const Vertex& other);
};

struct compareVertex
{
	bool operator()(const Vertex* vl, const Vertex* vr);
};

struct VertexHash
{
	size_t operator()(const Vertex& vertex) const
	{
		return std::hash<std::string>()(vertex.gp.to_string());
	}
};

struct VertexEqual
{
	bool operator()(const Vertex& v1, const Vertex& v2) const
	{
		return ((v1.gp.latitude == v2.gp.latitude) && (v1.gp.longitude == v2.gp.longitude));
	}
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