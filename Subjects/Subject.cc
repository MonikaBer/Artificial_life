//Andrzej Przybylski & Monika Berlinska
//Base class for all kind of creatures living in artificial world
#include"Subject.h"

Subject::Subject(int x, int y, int vel)
{
    xposition = x;
    yposition = y;
    velocity = vel;
}

int Subject::getXPosition()
{
    return xposition;
}

int Subject::getYPosition()
{
    return yposition;
}
