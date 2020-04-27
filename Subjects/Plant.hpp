//Andrzej Przybylski & Monika Berlinska
//Class for plants
#ifndef PLANT_H
#define PLANT_H

#include"Subject.hpp"

class Plant : public Subject{
    public:
        Plant(int x, int y) : Subject(x, y) {};
};

#endif