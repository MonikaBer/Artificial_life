//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#include <ctime>
#include <cstdlib>
#include "Animal.hpp"
#include "AnimalConstants.hpp"

using namespace std;


Animal::Animal(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : Subject(x, y) {
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

void Animal::thisTurn(bool reproductionPeriod, Coordinates &consumedSubjectPosition, Coordinates &childPosition) {
    Target target = determineTarget(reproductionPeriod);

    if (target == DEAD) {
        toDelete = true;
        return;
    }

    int leapsNr = 0;
    Coordinates targetPosition = make_pair(-1, -1);
    bool isTargetEncountered = lookAround(targetPosition, target);     // target could changed

    if (target == PARTNER) {
        if (isTargetEncountered) {
            reproduce(targetPosition, childPosition);
        } else {
            leapsNr = move(targetPosition, target);
        }
    } else if (target == FOOD) {
        if (isTargetEncountered) {
            eat(consumedSubjectPosition);
        } else {
            leapsNr = move(targetPosition, target);
        }
    } else if (target == SLEEP) {
        sleep();
    } else if (target == ESCAPE || target == NEUTRAL) {
        leapsNr = move(targetPosition, target);
    }

    updateParameters(leapsNr);
}

Target Animal::determineTarget(bool reproductionPeriod) {
    Target target = NEUTRAL;
    if (fullness == 0 || energy == 0 || lifeTime == maxLifeTime)
        target = DEAD;
    else if (reproductionPeriod && fullness >= 0.2*maxFullness && energy >= 0.2*maxEnergy)
        target = PARTNER;
    else if (fullness < 0.2*maxFullness)
        target = FOOD;
    else if (energy < 0.2*maxEnergy)
        target = SLEEP;
    else if (fullness < 0.5*maxFullness)
        target = FOOD;
    else if (energy < 0.3*maxEnergy || fullness > 0.85*maxFullness)
        target = SLEEP;
    else
        target = FOOD;
    return target;
}

int Animal::move(Coordinates targetPosition, Target target) {    //x, y -> target position; if x = -1, y = -1 -> no target
    int leapsNumber = 0;
//    if (target == ) {
//
//    }

    return leapsNumber;     //returns traveled distance
}

void Animal::eat(Coordinates &consumedSubjectPosition) {

}

void Animal::sleep() {
    energy += 0.1 * maxEnergy;
}

void Animal::reproduce(Coordinates targetPosition, Coordinates &childPosition) {
    //reproduce with another animal
}

void Animal::updateParameters (int leapsNr) {  //update fullness, energy and lifeTime
    fullness -= ((float)digestionRate/100.0) * maxFullness;
    if (fullness < 0)
        fullness = 0;
    energy -= leapsNr;
    if (energy < 0)
        energy = 0;
    lifeTime++;
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