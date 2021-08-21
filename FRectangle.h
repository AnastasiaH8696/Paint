#pragma once
#include "FPolygon.h"
class FRectangle: public FPolygon
{
	DECLARE_SERIAL(FRectangle)
public:
	FRectangle() {}
	FRectangle(CPoint p1, CPoint p2);
};

