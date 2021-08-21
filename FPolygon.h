#pragma once
#include "Figure.h"
class FPolygon :public Figure {
	DECLARE_SERIAL(FPolygon)
public:
	FPolygon() {}
	FPolygon(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};

