#include "STARSHIP.h"
#include <curses.h>
#include <windows.h>

STARSHIP::STARSHIP()
{
	x = 50;
	y = 15;
	hp = 3;
	ammo = 0;
}

void STARSHIP::draw(WINDOW* win)
{
	mvwprintw(win, y + 1, x, "|");
	mvwhline(win, y, x, '#', width);
	mvwhline(win, y + (height)-1, x, '#', width);
	mvwprintw(win, y + 1, x + width - 1, "|");
	mvwprintw(win, y + 1, x - 2, ">>");



	mvwprintw(win, y + (height / 2), x + width, "==");

	//mvwprintw(win, y, x, "a");		//wświetla kordy x i a

}

void STARSHIP::movement()
{
	if (GetAsyncKeyState(0x44))
	{
		x += speed;
	}
	if (GetAsyncKeyState(0x41))
	{
		x -= speed;
	}
	if (GetAsyncKeyState(0x57))
	{
		y -= speed/ySpeedModifier;
	}
	if (GetAsyncKeyState(0x53))
	{
		y += speed / ySpeedModifier;
	}

	if (x < 1)
	{
		x = 1;
	}
	if (x + width > 120)
	{
		x = 120 - width;
	}
	if (y < 1)
	{
		y = 1;
	}
	if (y + height > 30)
	{
		y = 30 - height;
	}
}

double STARSHIP::getX()
{
	return x;
}

double STARSHIP::getY()
{
	return y;
}

int STARSHIP::getWidth()
{
	return width;
}

int STARSHIP::getHeight()
{
	return height;
}
