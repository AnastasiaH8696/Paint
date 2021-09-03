#pragma once
#include "FPolygon.h"
class FTriangle: public FPolygon
{
	DECLARE_SERIAL(FTriangle)
	CPoint P3;
public:
	FTriangle() {}
	FTriangle(CPoint p1, CPoint p2);
	CPoint getP3() const { return P3; }
	void setP3(double x, double y) { P3.x = x; P3.y = y; }
	void Draw(CDC* dc) const;
	void Redefine(CPoint p1, CPoint p2);
	bool isInside(const CPoint& P) const;
	void FTriangle::onMove(CPoint c1, CPoint c2);
};


