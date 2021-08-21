#pragma once
#include "FPolygon.h"
class FTriangle: public FPolygon
{
	DECLARE_SERIAL(FTriangle)
public:
	FTriangle() {}
	FTriangle(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};


