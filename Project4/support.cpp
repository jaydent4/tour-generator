#include "support.h"


bool vertex::operator>(const vertex& other) const
{
	return (this->hs > other.hs);
}
bool vertex::operator<(const vertex& other) const
{
	return (this->hs < other.hs);
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