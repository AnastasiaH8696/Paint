#pragma once
#include "Figure.h"
class FLine :public Figure {
	DECLARE_SERIAL(FLine)
public:
	FLine() {}
	FLine(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};


