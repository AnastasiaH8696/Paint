#include "pch.h"
#include "FDStar.h"
IMPLEMENT_SERIAL(FDStar, CObject, 1)

FDStar::FDStar(CPoint p1, CPoint p2)
	:FPolygon(p1, p2)
{
}

void FDStar::Draw(CDC* dc) const
{
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	CPoint center = p1 + p2;
	center.x /= 2.0; center.y /= 2.0;
	double radius = abs(p1.x - p2.x) < abs(p1.y - p2.y) ? abs(p1.x - p2.x) / 2.0 : abs(p1.y - p2.y) / 2.0;
	CPoint vertices[12];
	double two_pi = atan(1) * 8;
	for (int i = 0; i < 12; i++)
	{
		if (i % 2 == 0)
		{
			vertices[i].x = center.x + radius / sqrt(3) * cos(two_pi / 12 * i);
			vertices[i].y = center.y + radius / sqrt(3) * sin(two_pi / 12 * i);
		}
		else
		{
			vertices[i].x = center.x + radius * cos(two_pi / 12 * i);
			vertices[i].y = center.y + radius * sin(two_pi / 12 * i);
		}
	}
	dc->Polygon(vertices, 12);
}