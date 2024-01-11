#include "STARSHIP.h"
#include <curses.h>
#include <windows.h>

STARSHIP::STARSHIP()
{
	x = 50;
	y = 15;
	hp = 100;
	speed = 0.05;
	width = 10;
	height = 3;
}

void STARSHIP::draw(WINDOW* win)
{
	mvwvline(win, y, x, '|', height);
	mvwhline(win, y - (height / 2), x, '-', width);
	mvwhline(win, y + (height), x, '-', width);
	mvwvline(win, y, x+width, '|', height);
	
	//mvwprintw(win, y, x, "a");		//wœwietla kordy x i a

}

void STARSHIP::movement(int keyPressed)
{
	switch (keyPressed)
	{
	case KEY_RIGHT:
	{
		int a = true;
		x += speed;
	}

	default:
		break;
	}
}
