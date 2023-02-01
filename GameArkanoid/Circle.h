#pragma once
#include "Plane.h"

class CCircle
{
public:
	CCircle();
	CPlane* plane;
	int x, y, r, dx, dy;
	bool startMove;
	CRect rect;
	void create(CRect*, CPlane*);
	void draw(CDC*);
	void move();
	void checkBorder();
	void checkPlane();
};

