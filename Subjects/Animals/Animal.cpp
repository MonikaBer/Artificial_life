//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "Animal.hpp"
#include "AnimalConstants.hpp"

using namespace std;


Animal::Animal(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : Subject(x, y) {
    maxEnergy = generateMaxEnergy();               //rand from 50 to 150
    maxFullness = generateMaxFullness();           //rand from 50 to 150
    velocity = generateVelocity();              //rand from 1 to 3
    digestionRate = generateDigestionRate();    //rand from 5 to 10 (in percents of maxFullness)

    energy = maxEnergy;
    fullness = maxFullness;
    lifeTime = AnimalConstants::ZERO_LIFE_TIME;

    maxLifeTime = maxLifeTimeSetting;              
    viewSize = viewSizeSetting;
}

void Animal::thisTurn(const AreaMap &areaMap, bool reproductionPeriod,
        Coordinates &consumedSubjectPosition, Coordinates &childPosition) {

    Target target = determineTarget(reproductionPeriod);    //decide what to do
    if (target == DEAD) {   //too bad crucial vital parameters (energy, fullness or lifeTime)
        toDelete = true;
        return;
    }

    int leapsNr = 0;
    Coordinates targetPosition = make_pair(-1, -1);
    bool isTargetEncountered = lookAround(areaMap, targetPosition, target);     // target could changed

    if (target == PARTNER) {
        if (isTargetEncountered) {
            putChildOnPosition(areaMap, targetPosition, childPosition);  //reproduce with partner
        } else {
            leapsNr = move(areaMap, targetPosition, target);    //go to partner
        }
    } else if (target == FOOD) {
        if (isTargetEncountered) {
            eat(targetPosition, consumedSubjectPosition);     //set position of consumed food
        } else {
            leapsNr = move(areaMap, targetPosition, target);  //go to food
        }
    } else if (target == SLEEP) {
        sleep();                                            //increase energy
    } else if (target == ESCAPE || target == NEUTRAL) {
        leapsNr = move(areaMap, targetPosition, target);    //escape or go anywhere
    }
    updateParameters(leapsNr);  //decrease energy, fullness and increase lifeTime
}

Target Animal::determineTarget(bool reproductionPeriod) {
    Target target = NEUTRAL;
    if (fullness == AnimalConstants::ZERO_FULLNESS || energy == AnimalConstants::ZERO_ENERGY || lifeTime == maxLifeTime)
        target = DEAD;
    else if (reproductionPeriod && fullness >= AnimalConstants::ESSENTIAL_PERCENT_OF_FULLNESS * maxFullness &&
                                                    energy >= AnimalConstants::ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy)
        target = PARTNER;
    else if (fullness < AnimalConstants::ESSENTIAL_PERCENT_OF_FULLNESS * maxFullness)
        target = FOOD;
    else if (energy < AnimalConstants::ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy)
        target = SLEEP;
    else if (fullness < AnimalConstants::TEMPERATE_PERCENT_OF_FULLNESS * maxFullness)
        target = FOOD;
    else if (energy < AnimalConstants::ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy ||
                                            fullness > AnimalConstants:: SUFFICIENT_PERCENT_OF_FULLNESS * maxFullness)
        target = SLEEP;
    else
        target = FOOD;
    return target;
}

int Animal::move(const AreaMap &areaMap, Coordinates targetPosition, Target target) { // targetPosition = (-1, -1) -> there is no target
    int leapsNumber = 0;
//    if (target == ) {
//
//    }

    return leapsNumber;     //returns traveled distance
}

void Animal::eat(Coordinates &targetPosition, Coordinates &consumedSubjectPosition) {
    consumedSubjectPosition.first = targetPosition.first;
    consumedSubjectPosition.second = targetPosition.second;
}

void Animal::sleep() {
    energy += AnimalConstants::PERCENT_OF_REGENERATION * maxEnergy;
}

void Animal::putChildOnPosition(const AreaMap &areaMap, Coordinates &targetPosition, Coordinates &childPosition) {
    //put child on position
}

void Animal::mixAttributes(const Animal &firstParent, const Animal &secondParent) {
    //reproduce with another animal
    (*this).setMaxEnergy(countChildAttribute(firstParent.getMaxEnergy(), secondParent.getMaxEnergy()));
    (*this).setMaxFullness(countChildAttribute(firstParent.getMaxFullness(), secondParent.getMaxFullness()));
    (*this).setVelocity(countChildAttribute(firstParent.getVelocity(), secondParent.getVelocity()));
    (*this).setDigestionRate(countChildAttribute(firstParent.getDigestionRate(), secondParent.getDigestionRate()));

    this->energy = this->maxEnergy;
    this->fullness = this->maxFullness;
}

void Animal::updateParameters (int leapsNr) {  //update fullness, energy and lifeTime
    fullness -= ((float)digestionRate / AnimalConstants::NUMBER_OF_PERCENTS) * maxFullness;
    if (fullness < AnimalConstants::ZERO_FULLNESS)
        fullness = AnimalConstants::ZERO_FULLNESS;
    energy -= leapsNr;
    if (energy < AnimalConstants::ZERO_ENERGY)
        energy = AnimalConstants::ZERO_ENERGY;
    lifeTime++;
}

//helpers
int Animal::generateMaxEnergy() {
    return (rand() % AnimalConstants::SIZEOF_MAX_ENERGY_RANGE + AnimalConstants::MIN_MAX_ENERGY);
}

int Animal::generateMaxFullness() {
    return (rand() % AnimalConstants::SIZEOF_MAX_FULLNESS_RANGE + AnimalConstants::MIN_MAX_FULLNESS);
}

int Animal::generateVelocity() {
    return (rand() % AnimalConstants::SIZEOF_VELOCITY_RANGE + AnimalConstants::MIN_VELOCITY);
}

int Animal::generateDigestionRate() {
    return (rand() % AnimalConstants::SIZEOF_DIGESTION_RATE_RANGE + AnimalConstants::MIN_DIGESTION_RATE);
}

int Animal::countChildAttribute(int firstParentAttr, int secondParentAttr) const {
    return (int)round((firstParentAttr + secondParentAttr) / AnimalConstants::PARENTS_NUMBER);
}

bool Animal::isMutation() {
    return rand() % AnimalConstants::MUTATIONS_FREQUENCY == AnimalConstants::MUTATION_OCCURRING_CONDITION;
}

void Animal::setChildMaxEnergy(int newMaxEnergy) {
    if (isMutation()) {                         //mutation occurred
        maxEnergy = generateMaxEnergy();
    } else {                                    // no mutation
        maxEnergy = newMaxEnergy;
    }
}

void Animal::setChildMaxFullness(int newMaxFullness) {
    if (isMutation()) {                         //mutation occurred
        maxFullness = generateMaxFullness();
    } else {                                    // no mutation
        maxFullness = newMaxFullness;
    }
}

void Animal::setChildVelocity(int newVelocity) {
    if (isMutation()) {                         //mutation occurred
        velocity = generateVelocity();
    } else {                                    // no mutation
        velocity = newVelocity;
    }
}

void Animal::setChildDigestionRate(int newDigestionRate) {
    if (isMutation()) {                                 //mutation occurred
        digestionRate = generateDigestionRate();
    } else {                                            // no mutation
        digestionRate = newDigestionRate;
    }
}

//getters
int Animal::getEnergy() const { return this->energy; }
int Animal::getFullness() const { return this->fullness; }
int Animal::getLifeTime() const { return this->lifeTime; }
int Animal::getVelocity() const { return this->velocity; }
int Animal::getDigestionRate() const { return this->digestionRate; }
int Animal::getMaxEnergy() const { return this->maxEnergy; }
int Animal::getMaxFullness() const { return this->maxFullness; }
int Animal::getMaxLifeTime() const { return this->maxLifeTime; }
int Animal::getViewSize() const { return this->viewSize; }

//setters
void Animal::setFullness(int newFullness) { fullness = newFullness; }
//void Animal::setLifeTime(int newLifeTme) { lifeTime = newLifeTime; }
void Animal::setEnergy(int newEnergy) { energy = newEnergy; }
void Animal::setVelocity(int newVelocity) { velocity = newVelocity; }
void Animal::setDigestionRate(int newDigestionRate) { digestionRate = newDigestionRate; }
void Animal::setMaxEnergy(int newMaxEnergy) { maxEnergy = newMaxEnergy; }
void Animal::setMaxFullness(int newMaxFullness) { maxFullness = newMaxFullness; }
//void Animal::setMaxLifeTime(int newMaxLifeTime) { maxLifeTime = newMaxLifeTime; }
//void Animal::setViewSize(int newViewSize) { viewSize = newViewSize; }