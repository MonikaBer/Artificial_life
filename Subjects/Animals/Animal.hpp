//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "../Subject.hpp"
#include <exception>

class Animal : public Subject {
    private:
        //variables which depend on time
        int energy;            //one unit of energy will being lost after each leap
        int fullness;      
        int lifeTime;          //number of motions done
        
        //variables which don't depend on time
        int velocity;        //number of leaps per one motion (?the smaller the faster??)
        int digestionRate;   //amount of fullness which is lost per each motion
        int maxEnergy;
        int maxFullness;
       
        //user settings
        int maxLifeTime;       //max number of motions
        int viewSize;          //field of view is a square and viewSize is its side
        //end of user settings

    public:
        Animal(int x, int y, int maxLifeTime, int viewSize);
        virtual ~Animal(){}
        
        int move(int x, int y);
        bool lookAround(int & x, int & y, int);
        void updateParameters(int leaps);
        void thisTurn(bool reproductionPeriod);    //main function deciding what to do
        void sleep();
        void reproduce();
        int getEnergy(); 
        int getFullness(); 
        int getLifeTime();
        int getVelocity();
        int getDigestionRate();
        int getMaxEnergy();
        int getMaxFullness();
        int getMaxLifeTime();
        int getViewSize();

        virtual void eat(Subject &eaten) = 0;
};

#endif