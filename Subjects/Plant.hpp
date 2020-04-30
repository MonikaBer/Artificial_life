//Andrzej Przybylski & Monika Berlinska
//Class for plants
#ifndef PLANT_HPP
#define PLANT_HPP

#include"Subject.hpp"

class Plant : public Subject {
    private:
        double caloricity;      //1.0 - for SuperPlant, 0.25 - for TypicalPlant

    public:
        Plant(int x, int y) : Subject(x, y) {};
};

#endif