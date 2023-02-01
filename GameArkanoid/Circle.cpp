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
	r = 5;
	x = rect->Width() / 2;
	y = rect->Height() - 71 - r - plane->planeHeight / 2;
	dx = 5;
	dy = -5;
}

void CCircle::draw(CDC* pDC) {
	pDC->MoveTo(x + r, y);
	pDC->AngleArc(x, y, r, 0, 360);
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

	if ((y + r >= plane->yCenter - plane->planeHeight / 2) && (x >= plane->xCenter - plane->planeWidth / 2) && (x <= plane->xCenter + plane->planeWidth / 2)) {
		dy *= -1;
	};

	if ((x + r >= plane->xCenter - plane->planeWidth / 2) && (y + r >= plane->yCenter - plane->planeHeight / 2) && (x - r <= plane->xCenter + plane->planeWidth / 2)) {
		dx *= -1;
	}

	if ((x - r <= plane->xCenter + plane->planeWidth / 2) && (x + r >= plane->xCenter - plane->planeWidth / 2) && ((y + r >= plane->yCenter - plane->planeHeight / 2))) {
		dx *= -1;
	}

	if (y + r >= rect.Height()) {
		plane->statusGame = 2;
	};
}

void CCircle::checkPlane() {
	
}