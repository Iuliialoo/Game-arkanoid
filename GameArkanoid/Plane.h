#pragma once
class CPlane
{
public:
	CPlane();
	int xCenter, yCenter, planeWidth, planeHeight;
	CRect rect;
	void create(CRect*);
	void draw(CDC*);
	int statusGame;
	void checkBorder();
};