#pragma once
#include "METEOR.h"
#include <curses.h>

class SCIENCEPACK :
    public METEOR
{
public:
    SCIENCEPACK();
    void draw(WINDOW* win);
    bool checkHitbox(double checkX, double checkY, int checkWidth, int checkHeight);
private:
    const int width = 1, height = 1;
};

