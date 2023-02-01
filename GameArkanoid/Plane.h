#pragma once
class CPlane
{
public:
	CPlane();
	int xCenter, yCenter, planeWidth, planeHeight, y1, y2, x1, x2;
	CRect rect;
	void create(CRect*);
	void draw(CDC*);
	int statusGame;
	void checkBorder();
};