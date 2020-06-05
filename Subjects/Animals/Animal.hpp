//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "../Subject.hpp"
#include "../../AreaMap.hpp"

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

        void thisTurn(AreaMap &areaMap, bool reproductionPeriod,
                Coordinates &consumedSubjectPosition, Coordinates &childPosition);  //main function deciding what to do
        Target determineTarget(bool reproductionPeriod);
        bool move(AreaMap &areaMap, Coordinates targetPosition, Target target);
        void eat(Coordinates &targetPosition, Coordinates &consumedSubjectPosition);
        void sleep();
        bool putChildOnPosition(AreaMap &areaMap, Coordinates &targetPosition, Coordinates &childPosition);
        void mixAttributes(const Animal &firstParent, const Animal &secondParent);
        void updateParameters(int leapsNr);

        //helpers
        int generateMaxEnergy();
        int generateMaxFullness();
        int generateVelocity();
        int generateDigestionRate();
        int countChildAttribute(int firstParentAttr, int secondParentAttr) const;
        bool isMutation();
        void setChildMaxEnergy(int newMaxEnergy);
        void setChildMaxFullness(int newMaxFullness);
        void setChildVelocity(int newVelocity);
        void setChildDigestionRate(int newDigestionRate);

        //getters
        int getEnergy() const;
        int getFullness() const; 
        int getLifeTime() const;
        int getVelocity() const;
        int getDigestionRate() const;
        int getMaxEnergy() const;
        int getMaxFullness() const;
        int getMaxLifeTime() const;
        int getViewSize() const;

        //setters
        void setFullness(int newFullness);
        // void setLifeTime(int newLifeTme);
        void setEnergy(int newEnergy);
        void setVelocity(int newVelocity);
        void setDigestionRate(int newDigestionRate);
        void setMaxEnergy(int newMaxEnergy);
        void setMaxFullness(int newMaxFullness); 
        // void setMaxLifeTime(int newMaxLifeTime);
        // void setViewSize(int newViewSize);

        virtual bool lookAround(const AreaMap &areaMap, Coordinates &targetPosition, Target &target) = 0;
};

#endif