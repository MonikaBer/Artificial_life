//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "../../helper.hpp"
#include "../Subject.hpp"

typedef enum {FOOD, PARTNER, SLEEP, ESCAPE, NEUTRAL, DEAD} Target;

class Animal : public Subject {
    protected:
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

        void thisTurn(bool reproductionPeriod, Coordinates &consumedSubjectPosition, Coordinates &childPosition);  //main function deciding what to do
        Target determineTarget(bool reproductionPeriod);
        int move(Coordinates targetPosition, Target target);
        void eat(Coordinates &consumedSubjectPosition);
        void sleep();
        void reproduce(Coordinates targetPosition, Coordinates &childPosition);
        void updateParameters(int leapsNr);

        int getEnergy();
        int getFullness(); 
        int getLifeTime();
        int getVelocity();
        int getDigestionRate();
        int getMaxEnergy();
        int getMaxFullness();
        int getMaxLifeTime();
        int getViewSize();

        virtual bool lookAround(Coordinates &targetPosition, Target &target) = 0;
};

#endif