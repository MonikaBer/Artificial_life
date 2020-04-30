//Andrzej Przybylski & Monika Berlinska
#ifndef SUPER_PLANT_HPP
#define SUPER_PLANT_HPP
#include "Plant.hpp"

class SuperPlant : public Plant {
    public:
        SuperPlant(int x, int y) : Plant(x, y) {
            this->setCaloricity(1.0);
        } 
};

#endif