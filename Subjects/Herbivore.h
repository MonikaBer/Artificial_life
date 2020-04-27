//Andrzej Przybylski & Monika Berlinska
//class representing herbivore animals
#ifndef HERBIVORE_H
#define HERBIVORE_H
#include"Animal.hpp"

class Herbivore : public Animal {
    public:
        virtual void eat(Subject &eaten);
        Herbivore(int x, int y) : Animal(x, y) {};
};

#endif