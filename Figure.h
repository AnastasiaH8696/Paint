#pragma once
#include "framework.h"
class Figure : public CObject {
	DECLARE_SERIAL(Figure) 
	CPoint P1;
	CPoint P2;
	COLORREF brushColor;
	COLORREF fillColor;
	int penStyle;
	int penSize;
public:
	Figure();
	Figure(CPoint p1, CPoint p2);
	void Serialize(CArchive& ar);
	virtual void Draw(CDC* dc) const { dc->Rectangle(P1.x, P1.y, P2.x, P2.y); };
	void MyDraw(CDC& dc);
	CPoint getP1() const { return P1; }	
	CPoint getP2() const { return P2; }
	COLORREF getBrushColor() const { return brushColor; }
	COLORREF getFillColor() const { return fillColor; }
	int getPenStyle() const { return penStyle; }
	int getPenSize() const { return penSize; }
	void setP1(double x, double y) { P1.x = x; P1.y = y; }
	void setP2(double x, double y) { P2.x = x; P2.y = y; }
	void setBrushColor(COLORREF bc) { brushColor = bc; }
	void setFillColor(COLORREF fc) { fillColor = fc; }
	void setPenStyle(int pS) { penStyle = pS; }
	void setPenSize(int pS) { penSize = pS; }
	virtual void Redefine(CPoint p1, CPoint p2) { P1 = p1; P2 = p2; }
	virtual bool isInside(const CPoint& P) const;
	//virtual void Shift(int dx, int dy);
	virtual void onMove(CPoint start, CPoint end);
};
