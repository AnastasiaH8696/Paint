#include "pch.h"
#include "FEllipse.h"

IMPLEMENT_SERIAL(FEllipse, CObject, 1)

FEllipse::FEllipse(CPoint p1, CPoint p2)
	:Figure(p1, p2)
{
}

void FEllipse::Draw(CDC* dc) const
{
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	dc->Ellipse(p1.x, p1.y, p2.x, p2.y);
}
