#include "pch.h"
#include "Circle.h"

CCircle::CCircle() {
	x = 0;
	y = 0;
	r = 0;
	dx = 0;
	dy = 0;
	rect = 0;
}

void CCircle::create(CRect* rect, CPlane* myPlane) {
	this->rect = rect;
	//startMove = false;
	plane = myPlane;
	r = 20;
	x = rect->Width() / 2;
	y = rect->Height() - 71 - r - plane->planeHeight / 2;
	dx = 5;
	dy = -5;
}

void CCircle::draw(CDC* pDC) {
	pDC->MoveTo(x + r, y);
	pDC->AngleArc(x, y, r, 0, 360);
	if (!startMove) {
		if (x - plane->planeWidth / 2 <= 0) x += 16;
		if (x + plane->planeWidth / 2 >= rect.Width()) x -= 16;
	}
}

void CCircle::move() {
	x += dx;
	y += dy;

	checkBorder();
}

void CCircle::checkBorder() {	
	if (x - r <= 0) dx *= -1;

	if (y - r <= 0) dy *= -1;

	if (x + r >= rect.Width()) dx *= -1;

	if (y + r >= rect.Height()) {
		plane->statusGame = 2;
	};
	
	
	int x1 = plane->xCenter - plane->planeWidth / 2,
	y1 = plane->yCenter - plane->planeHeight / 2,
	y2 = plane->yCenter + plane->planeHeight / 2,
	x2 = plane->xCenter + plane->planeWidth / 2;

	if (x < x1 && x + r >= x1 && y + r > y1) dx *= -1;
	if (x > x2 && x - r <= x2 && y + r > y1) dx *= -1;
	
	if (x + r >= x1 && x - r <= x2) {
		if (y < y1 && y + r >= y1) dy *= -1;
	}
}