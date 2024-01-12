#include "SCIENCEPACK.h"
#include <cstdlib>
#include <curses.h>

SCIENCEPACK::SCIENCEPACK()
{
	x = 120;
	y = rand() % 30;
	speedX = 0.3;
	speedY = 0;
}

void SCIENCEPACK::draw(WINDOW* win)
{
	wattron(win, COLOR_PAIR(4));
	mvwprintw(win, y, x, "#");
	wattroff(win, COLOR_PAIR(4));
}

bool SCIENCEPACK::checkHitbox(double checkX, double checkY, int checkWidth, int checkHeight)
{
	if ((checkX + checkWidth > x) && (checkX < x + width) && (checkY + checkHeight > y) && (checkY < y + height))
	{
		x = 130;
		y = rand() % 30;;
		return true;
	}

	return false;
}
