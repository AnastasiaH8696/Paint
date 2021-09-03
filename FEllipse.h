#pragma once
#include "Figure.h"
class FEllipse :public Figure {
	DECLARE_SERIAL(FEllipse)  
public:
	FEllipse() {}
	FEllipse(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
	bool isInside(const CPoint& P) const;
};


