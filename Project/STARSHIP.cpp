#include "STARSHIP.h"
#include <string>
#include <curses.h>
#include <windows.h>

STARSHIP::STARSHIP()
{
	x = 50;
	y = 15;
	hp = 3;
	ammo = 0;
	science = 0;
	shooted = 0;
}

void STARSHIP::draw(WINDOW* win)
{
	wattron(win, COLOR_PAIR(2));

	mvwprintw(win, y + 1, x, "|");
	mvwhline(win, y, x, '#', width);
	mvwhline(win, y + (height)-1, x, '#', width);
	mvwprintw(win, y + 1, x + width - 1, "|");
	mvwprintw(win, y + 1, x - 2, ">>");



	mvwprintw(win, y + (height / 2), x + width, "==");

	wattroff(win, COLOR_PAIR(2));

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

	if (x < 0)
	{
		x = 0;
	}
	if (x + width > 120)
	{
		x = 120 - width;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (y + height > 30)
	{
		y = 30 - height;
	}
}

void STARSHIP::drawHUD(WINDOW* win)
{
	mvwprintw(win, 1, 1, "HP: %d", hp);
	mvwprintw(win, 2, 1, "AMMO: %d", ammo);
	mvwprintw(win, 3, 1, "SCIENCE: %d", science);
}

void STARSHIP::moreAmmo(bool ammoPack)
{
	if (ammoPack == true)
	{
		ammo+=3;
	}
}

void STARSHIP::gatherScience(bool sciencePack)
{
	if (sciencePack == true)
	{
		science++;
	}
}

bool STARSHIP::shoot()
{
	if ((GetAsyncKeyState(VK_SPACE)) && (ammo > 0) && (shooted < 1))
	{
		ammo--;
		shooted = 25;
		return true;
	}

	if (shooted > 0)
	{
		shooted--;
	}

	return false;
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
