#pragma once
#include "METEOR.h"
#include <curses.h>
class AMMOPACK :
    public METEOR
{
public:
    AMMOPACK();
    void draw(WINDOW* win);
    bool checkHitbox(double checkX, double checkY, int checkWidth, int checkHeight);
private:
    int width = 1, height = 1;
};

