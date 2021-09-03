#include "pch.h"
#include "FTriangle.h"
IMPLEMENT_SERIAL(FTriangle, CObject, 1)

FTriangle::FTriangle(CPoint p1, CPoint p2)
	:FPolygon(p1, p2)
{
	P3.x = p1.x;
	P3.y = p1.y;
}

//TODO: Change to the right formula
void FTriangle::Draw(CDC* dc) const
{
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	CPoint p3 = getP3();

	CPoint TPoints[3] = { p1,p2,p3 };

	dc->Polygon(TPoints, 3);
}

void FTriangle::Redefine(CPoint start, CPoint end) {
	Figure::Redefine(start, end);

	CPoint p1 = getP1();
	CPoint p2 = getP2();
	CPoint p3;

	p3.x = abs(p2.x + p1.x) / 2;
	p3.y = p2.y;

	setP2(p2.x, p1.y);
	setP3(p3.x, p3.y);
}

bool FTriangle::isInside(const CPoint& P) const {
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	CPoint p3 = getP3();
	int d1, d2, d3;
	bool neg, pos;

	d1 = (P.x - p2.x) * (p1.y - p2.y) - (p1.x - p2.x) * (P.y - p2.y);
	d2 = (P.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (P.y - p3.y);
	d3 = (P.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (P.y - p1.y);

	neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(neg && pos);
}

void FTriangle::onMove(CPoint c1, CPoint c2)
{
	CPoint p3 = getP3();
	p3.x += (c1.x - c2.x);
	p3.y += (c1.y - c2.y);
	setP3(p3.x, p3.y);

	Figure::onMove(c1, c2);
}