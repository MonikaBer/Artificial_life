//Andrzej Przybylski & Monika Berlinska
#ifndef TYPICAL_PLANT_HPP
#define TYPICAL_PLANT_HPP
#include "Plant.hpp"

class TypicalPlant : public Plant { 
    public:
        TypicalPlant(int x, int y) : Plant(x, y) {
            caloricity = 0.25;
        }        
};

#endif