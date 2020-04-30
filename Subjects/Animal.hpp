//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "Subject.hpp"
#include <stdio.h>
#include <exception>

class Animal : public Subject {
    private:
        //view range in represented by ellipse that's why we need major and minor value
        int majorseeing;
        int minorseeing; 
        int direction;    //0 - N, 1 - NE, 2 - E, 3 - SE, 4 - S, 5 - SW, 6 - W, 7 - NW
        int energy;
        int fulness;
        int velocity;
        int maxEnergy;
        int maxFulness;
        int maxVelocity;

    public:
        Animal(int x, int y) : Subject(x, y) {}
        virtual ~Animal(){}
        
        void move();
        void lookAround();
        void setDirection(int dir);

        virtual void eat(Subject &eaten) = 0;
};

#endif