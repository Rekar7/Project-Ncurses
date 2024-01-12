#include "MISSILE.h"
#include <Windows.h>

MISSILE::MISSILE()
{
	x = 140;
	y = 3;
	speedX = 0;
	speedY = 0;
}

void MISSILE::draw(WINDOW* win)
{
	mvwprintw(win, y, x - 1, "~");
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, y, x, "=");
	wattroff(win, COLOR_PAIR(3));
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, y, x + 1, ">");
	wattroff(win, COLOR_PAIR(1));
}

void MISSILE::shoot(double xStarship, double yStarship,int widthStarship, int heightStarship)
{
		speedX = -1;
		x = xStarship + widthStarship;
		y = yStarship + heightStarship/2;
	
}
