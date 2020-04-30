//Andrzej Przybylski & Monika Berlinska
//class representing herbivore animals
#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP
#include"Animal.hpp"

class Herbivore : public Animal {
    private:
        double caloricity;       //for predator

    public:
        virtual void eat(Subject &eaten);
        Herbivore(int x, int y, int maxLifeTimeSetting, int viewSizeSetting);
        ~Herbivore() {}
};

#endif