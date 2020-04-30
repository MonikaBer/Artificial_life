//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#include <ctime>
#include <cstdlib>
#include "Animal.hpp"
using namespace std;


Animal::Animal(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : Subject(x, y) {
    srand(time(NULL));

    maxEnergy = (std::rand() % 101) + 50;      //rand from 50 to 150
    maxFulness = (std::rand() % 101) + 50;     //rand from 50 to 150
    velocity = (std::rand() % 3) + 1;          //rand from 1 to 3
    digestionRate = (std::rand() % 6) + 5;     //rand from 5 to 10
    energy = maxEnergy;                   
    fullness = maxFulness; 
    lifeTime = 0;                              

    maxLifeTime = maxLifeTimeSetting;              
    viewSize = viewSizeSetting;          
}

bool Animal::lookAround(int & x, int & y, int target) {
    //look for food/partner in the field of view, set position of food/partner and return true if success
    //otherwise return false and set x = -1, y = -1
    //target is food/partner

    return false;
}

int Animal::move(int x, int y){
    int leapsNumber = 0;

    //moving algorithm which set new position of animal, point is a position of found food
    //returns number of leaps during the motion
    
    return leapsNumber;
}

void Animal::updateParameters(int leapsNumber) {
    //update energy, fullness, lifeTime
}

void Animal::sleep() {
    //animal sleeps, regenerates
}

void Animal::reproduce() {
    //reproduce with another animal
}

//getters
int Animal::getEnergy() { return energy; }
int Animal::getFullness() { return fullness; }
int Animal::getLifeTime() { return lifeTime; }
int Animal::getVelocity() { return velocity; }
int Animal::getDigestionRate() { return digestionRate; }
int Animal::getMaxEnergy() { return maxEnergy; }
int Animal::getMaxFulness() { return maxFulness; }
int Animal::getMaxLifeTime() { return maxLifeTime; }
int Animal::getViewSize() { return viewSize; }