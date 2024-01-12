#include "AMMOPACK.h"
#include <curses.h>
#include <cstdlib>

AMMOPACK::AMMOPACK()
{
	x = 120;
	y = rand() % 30;;
	speedX = 0.3;
	speedY = 0;
}

void AMMOPACK::draw(WINDOW* win)
{
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, y, x, "#");
	wattroff(win, COLOR_PAIR(1));
}

bool AMMOPACK::checkHitbox(double checkX, double checkY, int checkWidth, int checkHeight)
{
	if ((checkX + checkWidth > x) && (checkX < x + width) && (checkY + checkHeight > y) && (checkY < y + height))
	{
		x = 130;
		y = 6;
		return true;
	}

	return false;
}
