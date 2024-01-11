#pragma once
#include <curses.h>

class STARSHIP
{
public:
	STARSHIP();
	void draw(WINDOW*);

	void movement();
private:
	double x, y;
	int hp;
	const int width=5, height=3;
	const double speed=0.5;
	const int ySpeedModifier = 2;	//prêdkoœæ osi y jest dwa razy wolniejsza

};

