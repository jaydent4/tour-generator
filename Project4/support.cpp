#include "support.h"

Vertex::Vertex(double g, double h, GeoPoint pt)
	: gs(g), hs(h), fs(g + h), gp(pt)
{}



bool compareVertex::operator()(const Vertex* vl, const Vertex* vr)
{
	if (vl->fs > vr->fs)
		return true;
	if (vl->fs < vr->fs)
		return false;
	return false;
}



//vertex::vertex(const vertex& other)
//	: gp(other.getGeoPoint())
//{
//	gs = other.gs;
//	hs = other.hs;
//	fs = other.gs + other.hs;
//}
//
//bool vertex::operator>(const vertex& other) const
//{
//	if (fs > other.fs)
//		return true;
//	else if (fs < other.fs)
//		return false;
//	else if (getGeoPoint().longitude > other.getGeoPoint().longitude)
//		return true;
//	else if (getGeoPoint().latitude > other.getGeoPoint().latitude)
//		return true;
//	else if (getGeoPoint().longitude < other.getGeoPoint().longitude)
//		return false;
//	else if (getGeoPoint().latitude < other.getGeoPoint().latitude)
//		return false;
//	else
//		return false;
//}
//bool vertex::operator<(const vertex& other) const
//{
//	if (fs < other.fs)
//		return true;
//	else if (fs > other.fs)
//		return false;
//	else if (getGeoPoint().longitude < other.getGeoPoint().longitude)
//		return true;
//	else if (getGeoPoint().latitude < other.getGeoPoint().latitude)
//		return true;
//	else if (getGeoPoint().longitude > other.getGeoPoint().longitude)
//		return false;
//	else if (getGeoPoint().latitude > other.getGeoPoint().latitude)
//		return false;
//	else
//		return false;
//}
//bool vertex::operator==(const vertex& other) const
//{
//	return (getGeoPoint().latitude == other.getGeoPoint().latitude && getGeoPoint().longitude == other.getGeoPoint().longitude);
//}
//
//void vertex::operator=(const vertex& other)
//{}
//
//const GeoPoint& vertex::getGeoPoint() const
//{
//	return gp;
//}