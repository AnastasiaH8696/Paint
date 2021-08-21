#include "pch.h"
#include "FRectangle.h"
IMPLEMENT_SERIAL(FRectangle, CObject, 1)

FRectangle::FRectangle(CPoint p1, CPoint p2)
	:FPolygon(p1, p2)
{
}
