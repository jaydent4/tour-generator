#include "support.h"

Vertex::Vertex(double g, double h, GeoPoint pt)
	: gs(g), hs(h), fs(g + h), gp(pt)
{}

bool Vertex::operator==(const Vertex& other)
{
	return ((gp.latitude == other.gp.latitude) && (gp.longitude == other.gp.longitude));
}

bool compareVertex::operator()(const Vertex* vl, const Vertex* vr)
{
	if (vl->fs > vr->fs)
		return true;
	if (vl->fs < vr->fs)
		return false;
	return false;
}