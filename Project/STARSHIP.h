#pragma once
#include <curses.h>

class STARSHIP
{
public:
	STARSHIP();
	void draw(WINDOW*);
	void movement();

	double getX();
	double getY();
	int getWidth();
	int getHeight();

private:
	double x, y;
	int hp, ammo;
	const int width=5, height=3;
	const double speed=0.5;
	const int ySpeedModifier = 2;	//pr�dko�� osi y jest dwa razy wolniejsza

};
