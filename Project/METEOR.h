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

protected:
	double x, y;
	double speedX, speedY;
	const int ySpeedModifier = 2;
private:
	int hp;
	const int width = 1, height = 1;	
};

