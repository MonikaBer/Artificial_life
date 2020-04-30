//Andrzej Przybylski & Monika Berlinska
//class representing predator animals
#ifndef PREDATOR_HPP
#define PREDATOR_HPP
#include"Animal.hpp"

class Predator : public Animal {
    public:
        virtual void eat(Subject &eaten);
        Predator(int x, int y);
        ~Predator() {}
};

#endif