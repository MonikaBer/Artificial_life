//Andrzej Przybylski & Monika Berlinska
//class representing herbivore animals
#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP
#include "Animal.hpp"

class Herbivore : public Animal {
    private:
        double caloricity;       //for predator

    public:
        Herbivore(int x, int y, int maxLifeTimeSetting, int viewSizeSetting);
        ~Herbivore() {}

        bool lookAround(AreaMap &areaMap, Coordinates &targetPosition, Target &target, bool reproductionPeriod);
};

#endif