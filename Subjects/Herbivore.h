//Andrzej Przybylski & Monika Berlinska
//class representing herbivore animals
#include"Animal.hpp"

class Herbivore : public Animal {
    public:
        virtual void eat(Subject &eaten);
        Herbivore(int x, int y) : Animal(x, y) {};
};