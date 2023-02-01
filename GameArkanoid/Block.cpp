#include "pch.h"
#include "Block.h"

CBlock::CBlock() {
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

void CBlock::create(int x1, int y1, int x2, int y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void CBlock::draw(CDC* pDC, CCircle* myCircle) {
	pDC->MoveTo(x1, y1);
	pDC->Rectangle(x1, y1, x2, y2);
}

void CBlock::checkCircle(CCircle* myCircle) {
	if ((myCircle->y - myCircle->r <= y2) && (myCircle->x >= x1) && (myCircle->x <= x2) || (myCircle->y + myCircle->r <= y1) && (myCircle->x >= x1) && (myCircle->x <= x2)) {
		myCircle->dy *= -1;
	}
	if ((myCircle->x - myCircle->r < x2) && (myCircle->y < y1) && (myCircle->y > y2) || (myCircle->x + myCircle->r > x1) && (myCircle->y < y1) && (myCircle->y > y2)) {
		myCircle->dx *= -1;
	}
}

bool CBlock::checkCircleTo(CCircle* myCircle) {
	if ((myCircle->y - myCircle->r <= y2) && (myCircle->x >= x1) && (myCircle->x <= x2)) {
		return true;
	}
	return false;
}