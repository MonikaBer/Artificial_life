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
      + AnimalConstants::MIN_DIGESTION_RATE;                                        //rand from 5 to 10
    
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

void Animal::updateParameters (int leapsNumber) {
    //update energy, fullness, lifeTime
}

void Animal::sleep() {
    //animal sleeps, regenerates
}

void Animal::reproduce() {
    //reproduce with another animal
}

void Animal::thisTurn(bool reproductionPeriod) {

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