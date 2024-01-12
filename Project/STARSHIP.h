#pragma once
#include <curses.h>

class STARSHIP
{
public:
	STARSHIP();
	void draw(WINDOW*);
	void movement();
	void drawHUD(WINDOW*);
	void scoreUpdate(int type);
	bool moreAmmo(bool ammoPack);
	bool gatherScience(bool sciencePack);
	bool shoot();

	double getX();
	double getY();
	int getWidth();
	int getHeight();
	int getScore();
	int getHighScore();
	void setHighScore(int a);

private:
	int shooted;
	double x, y;
	int score, highScore, ammo,science;
	const int width=5, height=3;
	const double speed=0.5;
	const int ySpeedModifier = 2;	//prêdkoœæ osi y jest dwa razy wolniejsza

};

