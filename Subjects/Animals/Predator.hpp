//Andrzej Przybylski & Monika Berlinska
//class representing predator animals
#ifndef PREDATOR_HPP
#define PREDATOR_HPP
#include "Animal.hpp"

class Predator : public Animal {
    public:
        Predator(int x, int y, int maxLifeTimeSetting, int viewSizeSetting);
        ~Predator() {}

        bool lookAround(Coordinates &targetPosition, Target &target);
};

#endif