#pragma once
#include <curses.h>

class METEOR
{
public:
	METEOR();
	void draw(WINDOW*);
	void movement();
	void spawn();

	bool outsideMap();
	double getX();
	double getY();
	int getWidth();
	int getHeight();

	bool checkHitbox(double checkX, double checkY, int checkWidth, int checkHeight);

protected:
	double x, y;
	double speedX, speedY;
	//int ySpeedModifier = 2;
private:
	int width = 2, height = 2;	
};

