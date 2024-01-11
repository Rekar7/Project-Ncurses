#pragma once
#include <curses.h>

class METEOR
{
public:
	METEOR();
	void draw(WINDOW*);
	void movement();

	double getX();
	double getY();
	int getWidth();
	int getHeight();

	bool checkHitbox(double checkX, double checkY, int checkWidth, int checkHeight);

private:
	double x, y;
	int hp;
	const int width = 5, height = 3;
	double speedX, speedY;
	const int ySpeedModifier = 2;
};

