#pragma once
#include "METEOR.h"
class MISSILE :
    public METEOR
{
public:
    MISSILE();
    void draw(WINDOW* win);
    void shoot(double xStarship, double yStarship, int widthStarship, int heightStarship);
private:
    const int width = 2, height = 1;
};

