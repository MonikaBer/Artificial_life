//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#include <ctime>
#include <cstdlib>
#include "Animal.hpp"
#include "AnimalConstants.hpp"
using namespace std;


Animal::Animal (int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : Subject(x, y) {
    maxEnergy = (std::rand() % AnimalConstants::SIZEOF_MAX_ENERGY_RANGE)
      + AnimalConstants::MIN_MAX_ENERGY;                                            //rand from 50 to 150
    maxFullness = (std::rand() % AnimalConstants::SIZEOF_MAX_FULLNESS_RANGE)
      + AnimalConstants::MIN_MAX_FULLNESS;                                          //rand from 50 to 150
    velocity = (std::rand() % AnimalConstants::SIZEOF_VELOCITY_RANGE)
      + AnimalConstants::MIN_VELOCITY;                                              //rand from 1 to 3
    digestionRate = (std::rand() % AnimalConstants::SIZEOF_DIGESTION_RATE_RANGE)
      + AnimalConstants::MIN_DIGESTION_RATE;                                        //rand from 5 to 10 (in percents of maxFullness)

    energy = maxEnergy;
    fullness = maxFullness;
    lifeTime = 0;

    maxLifeTime = maxLifeTimeSetting;              
    viewSize = viewSizeSetting;
}

bool Animal::lookAround (int &x, int &y, int target) {
    //look for food/partner in the field of view, set position of food/partner and return true if success
    //otherwise return false and set x = -1, y = -1
    //target is food/partner

    return true;
}

int Animal::move (int x, int y){
    int leapsNumber = 0;

    //moving algorithm which set new position of animal, point is a position of found food
    //returns number of leaps during the motion
    
    return leapsNumber;
}

void Animal::updateParameters (int leapsNr) {  //update fullness, energy and lifeTime
    fullness -= ((float)digestionRate/100.0) * maxFullness;
    if (fullness < 0)
        fullness = 0;
    energy -= leapsNr;
    if (energy < 0) {
        energy = 0;
    }
    lifeTime++;
}

void Animal::sleep() {
    //animal sleeps, regenerates
}

void Animal::reproduce() {
    //reproduce with another animal
}

void Animal::thisTurn(bool reproductionPeriod, Coordinates &consumedSubjectPosition, Coordinates &childPosition) {
    if (fullness == 0 || energy == 0 || lifeTime == maxLifeTime) {
        toDelete = true;
        return;
    }
    int leapsNr = 0;
    if (reproductionPeriod && fullness >= 0.2*maxFullness && energy >= 0.2*maxEnergy) {
        //look for partner
        //if partner is found -> reproduce and set childPosition
        //update leapsNr
    } else {
        if (fullness < 0.2*maxFullness) {
            //look for food
            //update leapsNr
        } else if (energy < 0.2*maxEnergy) {
            //sleep
        } else if (fullness < 0.5*maxFullness) {
            //look for food
            //update leapsNr
        } else if (energy < 0.3*maxEnergy || fullness > 0.85*maxFullness) {
            //sleep
        } else {
            //look for food
            //update leapsNr
        }
        //set consumedSubjectPosition if animal found food
    }

    updateParameters(leapsNr);
}

//getters
int Animal::getEnergy() { return energy; }
int Animal::getFullness() { return fullness; }
int Animal::getLifeTime() { return lifeTime; }
int Animal::getVelocity() { return velocity; }
int Animal::getDigestionRate() { return digestionRate; }
int Animal::getMaxEnergy() { return maxEnergy; }
int Animal::getMaxFullness() { return maxFullness; }
int Animal::getMaxLifeTime() { return maxLifeTime; }
int Animal::getViewSize() { return viewSize; }