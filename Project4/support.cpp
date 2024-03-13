#include "support.h"

vertex::vertex(const vertex& other)
	: gp(other.getGeoPoint())
{
	gs = other.gs;
	hs = other.hs;
	fs = other.gs + other.hs;
}

bool vertex::operator>(const vertex& other) const
{
	return (this->fs > other.fs);
}
bool vertex::operator<(const vertex& other) const
{
	return (this->fs < other.fs);
}
bool vertex::operator==(const vertex& other) const
{
	return (getGeoPoint().latitude == other.getGeoPoint().latitude && getGeoPoint().longitude == other.getGeoPoint().longitude);
}

void vertex::operator=(const vertex& other)
{}

const GeoPoint& vertex::getGeoPoint() const
{
	return gp;
}