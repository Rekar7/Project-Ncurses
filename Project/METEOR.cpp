#include "METEOR.h"
#include <cstdlib>

METEOR::METEOR()
{
	x = 120;
	y = rand() % 30;;
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
	//y += speedY / ySpeedModifier;
}

void METEOR::spawn()
{
	y = rand() % 30;
}

bool METEOR::outsideMap()
{
	if (x < -10)
	{
		return true;
	}
	if (x + width > 130)
	{
		return true;
	}
	if (y < -10)
	{
		return true;
	}
	if (y + height > 40)
	{
		return true;
	}

	return false;
}

double METEOR::getX()
{
	return x;
}

double METEOR::getY()
{
	return y;
}

int METEOR::getWidth()
{
	return width;
}

int METEOR::getHeight()
{
	return height;
}

bool METEOR::checkHitbox(double checkX, double checkY, int checkWidth, int checkHeight)
{
	if ((checkX + checkWidth > x) && (checkX < x + width) && (checkY + checkHeight > y) && (checkY < y + height))
	{
		return true;
	}

	return false;
}
