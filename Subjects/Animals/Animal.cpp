//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <algorithm>
#include "Animal.hpp"
#include "AnimalConstants.hpp"

using namespace std;


Animal::Animal(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : Subject(x, y) {
    maxEnergy = generateMaxEnergy();                //rand from 50 to 150
    maxFullness = generateMaxFullness();            //rand from 50 to 150
    velocity = generateVelocity();                  //rand from 1 to 3
    digestionRate = generateDigestionRate();        //rand from 5 to 10 (in percents of maxFullness)

    energy = maxEnergy;
    fullness = maxFullness;
    lifeTime = AnimalConstants::ZERO_LIFE_TIME;

    maxLifeTime = maxLifeTimeSetting;              
    viewSize = viewSizeSetting;
}

void Animal::thisTurn(AreaMap &areaMap, bool reproductionPeriod, Coordinates &partnerPosition,
        Coordinates &consumedSubjectPosition, Coordinates &childPosition) {

    if (!reproductionPeriod)
        this->afterReproduction = false;

    Target target = determineTarget(reproductionPeriod);    //decide what to do
    if (target == DEAD) {   //too bad crucial vital parameters (energy, fullness or lifeTime)
        toDelete = true;
        return;
    }

    int leapsNumber = 0;
    Coordinates targetPosition = make_pair(-1, -1);  
    bool isTargetEncountered = false;
    
    for (; leapsNumber < this->velocity; ++leapsNumber) {
        targetPosition.first = -1;
        targetPosition.second = -1;
        isTargetEncountered = lookAround(areaMap, targetPosition, target, reproductionPeriod);  // target could changed

        if (target == PARTNER) {
            if (isTargetEncountered) {  //reproduce with partner
                if (putChildOnPosition(areaMap, targetPosition, childPosition)) {  //successfully child creation
                    partnerPosition = targetPosition;
                    this->afterReproduction = true;  //prohibit reproduction in this reproductionPeriod
                }
                leapsNumber++;
                break;  //after trial of reproduction this animal waits for the next turn
            } else {    //go to partner
                if (oneLeapMove(areaMap, targetPosition, target)) {  //successful motion
                    leapsNumber++;
                } else {                 //all adjacent positions occupied, so go sleep and finished this turn
                    sleep();
                    break;
                }
            }
        } else if (target == FOOD) {
            if (isTargetEncountered) {
                eat(targetPosition, consumedSubjectPosition);     //increase fullness and set position of consumed food
                leapsNumber++;
                break;          //after eating this animal waits for the next turn
            } else {  //go to food
                if (oneLeapMove(areaMap, targetPosition, target)) {  //successfully motion
                    leapsNumber++;
                } else {  //all adjacent positions occupied, so go sleep and finished this turn
                    sleep();
                    break;
                }
            }
        } else if (target == SLEEP) {   //sleep lasts whole turn
            sleep(); 
            break;                                           //increase energy
        } else if (target == ESCAPE || target == NEUTRAL) {  //escape or go anywhere
            if (oneLeapMove(areaMap, targetPosition, target)) {    
                leapsNumber++;
            } else {  //all adjacent positions occupied, so go sleep and finished this turn
                sleep();
                break;
            }
        }
    }
    
    updateParameters(leapsNumber);  //decrease energy, fullness and increase lifeTime
}

Target Animal::determineTarget(bool reproductionPeriod) {
    Target target = NEUTRAL;
    if (fullness == AnimalConstants::ZERO_FULLNESS || energy == AnimalConstants::ZERO_ENERGY || lifeTime == maxLifeTime)
        target = DEAD;
    else if (!this->afterReproduction && reproductionPeriod && fullness >= AnimalConstants::ESSENTIAL_PERCENT_OF_FULLNESS * maxFullness &&
                                                    energy >= AnimalConstants::ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy)

        target = PARTNER;
    else if (this->afterReproduction && fullness >= AnimalConstants::ESSENTIAL_PERCENT_OF_FULLNESS * maxFullness &&
                                        energy >= AnimalConstants::ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy)
        target = SLEEP;
    else if (fullness < AnimalConstants::ESSENTIAL_PERCENT_OF_FULLNESS * maxFullness)
        target = FOOD;
    else if (energy < AnimalConstants::ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy)
        target = SLEEP;
    else if (fullness < AnimalConstants::TEMPERATE_PERCENT_OF_FULLNESS * maxFullness)
        target = FOOD;
    else if (energy < AnimalConstants::ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy &&
                                            fullness > AnimalConstants:: SUFFICIENT_PERCENT_OF_FULLNESS * maxFullness)
        target = SLEEP;
    else
        target = FOOD;
    return target;
}

void Animal::eat(Coordinates &targetPosition, Coordinates &consumedSubjectPosition) {
    this->fullness = this->maxFullness;  //temporary solution
    consumedSubjectPosition = targetPosition;
}

void Animal::sleep() {
    energy += AnimalConstants::PERCENT_OF_REGENERATION * maxEnergy;
}

bool Animal::putChildOnPosition(AreaMap &areaMap, Coordinates &targetPosition, Coordinates &childPosition) {
    //look for free adjacent position
    Coordinates currentPosition = make_pair(this->position.first, this->position.second);
    vector<Coordinates> freePositions = areaMap.returnFreeAdjacentPositions(currentPosition);
    if (freePositions.empty()) {  //all adjacent position occupied -> child perishs
        childPosition.first = -1;
        childPosition.second = -1;
        return false;
    }
    int randIndex = rand() % freePositions.size();  // rand new position to choose
    childPosition = freePositions[randIndex];
    return true;
}

bool Animal::oneLeapMove(AreaMap &areaMap, Coordinates targetPosition, Target target) { // targetPosition = (-1, -1) -> there is no target
    Coordinates currentPosition = make_pair(this->position.first, this->position.second);
    vector<Coordinates> freePositions = areaMap.returnFreeAdjacentPositions(currentPosition);
    if (freePositions.empty())
        return false;                                  //adjacent positions are occupied
    if (target == NEUTRAL) {
        int randIndex = rand() % freePositions.size();  // rand new position to choose
        this->position = freePositions[randIndex];
    } else {
        vector<float> distances = countDistancesFromTarget(targetPosition, freePositions);
        float desiredDistance = -1.0;
        if (target == PARTNER || target == FOOD) {
            desiredDistance = *min_element(distances.begin(), distances.end());
        } else if (target == ESCAPE) {
            desiredDistance = *max_element(distances.begin(), distances.end());
        }
        int selectedPosition = *find(distances.begin(), distances.end(), desiredDistance);
        this->position = freePositions[selectedPosition];
    }

    //change animal position (in areaMap too):
    map<Coordinates, Subject*>::iterator it = areaMap.find(currentPosition);
    if (it != areaMap.end()) {
        areaMap.erase(it);  //delete previous position in areaMap
        areaMap.insert(this->position, this);  //add new position to areaMap
    } else {
        //exception: animal position avoided from areaMap
    }
    return true;  //successfully motion
}

void Animal::mixAttributes(Animal *firstParent, Animal *secondParent) {
    //reproduce with another animal
    (*this).setMaxEnergy(countChildAttribute((*firstParent).getMaxEnergy(), (*secondParent).getMaxEnergy()));
    (*this).setMaxFullness(countChildAttribute((*firstParent).getMaxFullness(), (*secondParent).getMaxFullness()));
    (*this).setVelocity(countChildAttribute((*firstParent).getVelocity(), (*secondParent).getVelocity()));
    (*this).setDigestionRate(countChildAttribute((*firstParent).getDigestionRate(), (*secondParent).getDigestionRate()));

    this->energy = this->maxEnergy;
    this->fullness = this->maxFullness;
}

void Animal::updateParameters (int leapsNumber) {  //update fullness, energy and lifeTime
//     fullness -= ((float)digestionRate / AnimalConstants::NUMBER_OF_PERCENTS) * maxFullness;
//     if (fullness < AnimalConstants::ZERO_FULLNESS)
//         fullness = AnimalConstants::ZERO_FULLNESS;
//     energy -= leapsNumber;
//     if (energy < AnimalConstants::ZERO_ENERGY)
//         energy = AnimalConstants::ZERO_ENERGY;
     //lifeTime++;
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

bool Animal::isVisibleForAnimal(Coordinates anotherPosition) {
    return anotherPosition.first >= this->position.first - (this->viewSize / 2.0) &&
           anotherPosition.first <= this->position.first + (this->viewSize / 2.0) &&
           anotherPosition.second >= this->position.second - (this->viewSize / 2.0) &&
           anotherPosition.second <= this->position.second + (this->viewSize / 2.0);
}

bool Animal::isEncountered(Coordinates position) {
    return position.first >= this->position.first - 1 &&
           position.first <= this->position.first + 1 &&
           position.second >= this->position.second - 1 &&
           position.second <= this->position.second + 1;
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