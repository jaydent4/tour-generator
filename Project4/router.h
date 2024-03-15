#ifndef ROUTER_H
#define ROUTER_H

#include <set>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>

#include "base_classes.h"
#include "hashmap.h"
#include "geotools.h"

class Router : public RouterBase
{
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const; // finds the route between GeoPoints
private:
	const GeoDatabaseBase& gdb;
};

struct Vertex
{
	Vertex(double g, double h, GeoPoint pt);
	double gs; // distance of path
	double hs; // distance from end
	double fs; // gs + hs
	GeoPoint gp;
	bool operator==(const Vertex& other);
};

struct compareVertex // compares f score of vertices
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

#endif // ROUTER_H
