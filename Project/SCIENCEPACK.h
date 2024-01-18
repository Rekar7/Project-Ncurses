#pragma once
#include "METEOR.h"
#include <curses.h>

class SCIENCEPACK :
    public METEOR
{
public:
    SCIENCEPACK();
    void draw(WINDOW* win);
private:
    int width = 1, height = 1;
};

