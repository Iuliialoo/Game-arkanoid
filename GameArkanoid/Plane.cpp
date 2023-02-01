#include "pch.h"
#include "Plane.h"

CPlane::CPlane() {
	planeWidth = 0;
	planeHeight = 0;
	xCenter = 0;
	yCenter = 0;
	//statusGame = true;
}

void CPlane::create(CRect* rect) {
	this->rect = rect;
	planeWidth = 500;
	planeHeight = 24;
	xCenter = rect->Width() / 2;
	yCenter = rect->Height() - 70;
}

void CPlane::draw(CDC* pDC) {
	pDC->MoveTo(xCenter, yCenter);
	pDC->Rectangle(xCenter - planeWidth / 2, yCenter + planeHeight / 2, xCenter + planeWidth / 2, yCenter - planeHeight / 2);
	checkBorder();
}

void CPlane::checkBorder() {
	if (xCenter - planeWidth / 2 <= 0) xCenter += 11;
	if (xCenter + planeWidth / 2 >= rect.Width()) xCenter -= 11;
}