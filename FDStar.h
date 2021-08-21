#pragma once
#include "FPolygon.h"
class FDStar: public FPolygon
{
	DECLARE_SERIAL(FDStar)
public:
	FDStar() {}
	FDStar(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};

