#include "pch.h"
#include "Figure.h"

IMPLEMENT_SERIAL(Figure, CObject, 1)

Figure::Figure()
{
	penSize = 1;
	penStyle = PS_SOLID;
	brushColor = RGB(0, 0, 0);
	fillColor = RGB(255, 255, 255);
}

Figure::Figure(CPoint p1, CPoint p2) :
	P1(p1), P2(p2)
{
	penSize = 1;
	penStyle = PS_SOLID;
	brushColor = RGB(0, 0, 0);
	fillColor = RGB(255, 255, 255);
}

void Figure::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << P1;
		ar << P2;
	}
	else // Loading, not storing
	{
		ar >> P1;
		ar >> P2;
	}
}


bool Figure::isInside(const CPoint& P) const
{
	return (P1.x <= P.x && P.x <= P2.x || P1.x >= P.x && P.x >= P2.x) &&
		(P1.y <= P.y && P.y <= P2.y || P1.y >= P.y && P.y >= P2.y);
}
void Figure::Shift(int dx, int dy)
{
	P1 = P1 + CPoint(dx, dy);
	P2 = P2 + CPoint(dx, dy);
}

void Figure::onMove(CPoint start, CPoint end, CDC *dc)
{
	int deltaX, deltaY;
	deltaX = end.x - start.x;
	deltaY = end.y - start.y;
	dc->Rectangle(P1.x + deltaX, P1.y + deltaY, P2.x + deltaX, P2.y + deltaY);
}

