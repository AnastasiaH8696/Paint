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

void Figure::MyDraw(CDC& dc)
{
	CPen pen;
	CPen* oldPen;
	pen.CreatePen(penStyle, penSize, brushColor);
	oldPen = dc.SelectObject(&pen);
	CBrush brush(fillColor);
	CBrush* oldBrush;
	oldBrush = dc.SelectObject(&brush);

	Draw(&dc);

	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
}

void Figure::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << P1;
		ar << P2;
		ar << fillColor;
		ar << brushColor;
		ar << penSize;
		ar << penStyle;
	}
	else // Loading, not storing
	{
		ar >> P1;
		ar >> P2;
		ar >> fillColor;
		ar >> brushColor;
		ar >> penSize;
		ar >> penStyle;
	}
}


bool Figure::isInside(const CPoint& P) const
{
	/*return (P1.x <= P.x && P.x <= P2.x || P1.x >= P.x && P.x >= P2.x) &&
		(P1.y <= P.y && P.y <= P2.y || P1.y >= P.y && P.y >= P2.y);*/

	int xx0 = 0, yy0 = 0, xx2 = 0, yy2 = 0;

	xx0 = P1.x > P2.x ? P2.x : P1.x;
	xx2 = P1.x < P2.x ? P2.x : P1.x;

	yy0 = P1.y > P2.y ? P2.y : P1.y;
	yy2 = P1.y < P2.y ? P2.y : P1.y;

	if (xx0 <= P.x && P.x <= xx2)
	{
		if (yy0 <= P.y && P.y <= yy2)
		{
			return true;
		}

	}

	return false;
}
//void Figure::Shift(int dx, int dy)
//{
//	P1 = P1 + CPoint(dx, dy);
//	P2 = P2 + CPoint(dx, dy);
//}

void Figure::onMove(CPoint start, CPoint end)
{
	P2.x += (start.x - end.x);
	P2.y += (start.y - end.y);
	P1.x = start.x;
	P1.y = start.y;
}

