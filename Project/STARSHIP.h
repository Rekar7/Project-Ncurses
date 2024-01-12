#pragma once
#include <curses.h>

class STARSHIP
{
public:
	STARSHIP();
	void draw(WINDOW*);
	void movement();
	void drawHUD(WINDOW*);
	void moreAmmo(bool ammoPack);
	void gatherScience(bool sciencePack);
	bool shoot();

	double getX();
	double getY();
	int getWidth();
	int getHeight();

private:
	int shooted;
	double x, y;
	int hp, ammo,science;
	const int width=5, height=3;
	const double speed=0.5;
	const int ySpeedModifier = 2;	//prêdkoœæ osi y jest dwa razy wolniejsza

};

