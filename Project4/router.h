#ifndef ROUTER_H
#define ROUTER_H

#include <set>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <string>
#include <string.h>

#include "base_classes.h"
#include "HashMap.h"
#include "geotools.h"
#include "support.h"

class Router : public RouterBase
{
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	const GeoDatabaseBase& gdb;
};

#endif // ROUTER_H
