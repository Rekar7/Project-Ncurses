#pragma once
#include <curses.h>

class STARSHIP
{
public:
	STARSHIP();
	void draw(WINDOW*);

	void movement(int);
private:
	int x, y, hp;
	int width, height;
	double speed;
	int ySpeedModifier = 2;	//prêdkoœæ osi y jest dwa razy wolniejsza

};

