#include "METEOR.h"

METEOR::METEOR()
{
	hp = 1;
	x = 120;
	y = 15;
	speedX = 0.2;
	speedY = 0;
}

void METEOR::draw(WINDOW* win)
{
	mvwhline(win, y, x, '#', 2);
	mvwhline(win, y - 1, x, '#', 2);
}

void METEOR::movement()
{
	x -= speedX;
	y += speedY / ySpeedModifier;
}

bool METEOR::checkHitbox(double checkX, double checkY, int checkWidth, int checkHeight)
{
	if ((checkX + checkWidth > x) && (checkX < x + width) && (checkY + checkHeight > y) && (checkY < y + height))
	{
		return true;
	}

	return false;
}
