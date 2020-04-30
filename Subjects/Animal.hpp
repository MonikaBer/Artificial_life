//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#ifndef ANIMAL_H
#define ANIMAL_H
#include"Subject.hpp"
#include<stdio.h>
#include<exception>

class Animal : public Subject{
    private:
        int velocity;
        //view range in represented by ellipse that's why we need major and minor value
        int majorseeing;
        int minorseeing;
        //it would be simple to use 4 direction up, down, right and left 
        int direction;
        int energy;
        int fulness;

    public:
        Animal(int x, int y) : Subject(x, y){};
        virtual ~Animal(){};
        void move()
        {
            printf("moving algorithm");
        }
        void lookAround()
        {
            printf("Checking if something is in seeing area");
        }
        void setDirection(int dir)
        {
            std::exception ex;
            if(dir<1 || dir>4)
                throw ex;
            direction = dir;
        }
        virtual void eat(Subject &eaten) = 0;
};
#endif