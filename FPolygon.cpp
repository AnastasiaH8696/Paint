#include "pch.h"
#include "FPolygon.h"
IMPLEMENT_SERIAL(FPolygon, CObject, 1)

FPolygon::FPolygon(CPoint p1, CPoint p2)
	:Figure(p1, p2)
{
}

void FPolygon::Draw(CDC* dc) const
{
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	dc->Rectangle(p1.x, p1.y, p2.x, p2.y);
}
