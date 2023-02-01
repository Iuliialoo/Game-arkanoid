#pragma once
#include "Circle.h"

class CBlock
{
public:
	CBlock();
	int x1, y1, x2, y2;
	void create(int, int, int, int);
	void draw(CDC*, CCircle*);
	bool checkCircle(CCircle*);
};

