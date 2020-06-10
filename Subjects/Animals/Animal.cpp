//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <algorithm>
#include "Animal.hpp"
#include "AnimalConstants.hpp"

using namespace std;


Animal::Animal(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : Subject(x, y) {
    maxEnergy = generateMaxEnergy();                //rand from 50 to 150
    maxFullness = generateMaxFullness();            //rand from 50 to 150 for Herbivores, for Predators 100-200
    velocity = generateVelocity();                  //for Herbivore from 1 to 3, Predators: 2-5
    digestionRate = generateDigestionRate();        //rand from 5 to 10 (in percents of maxFullness)
    defaultTarget = generateDefaultTarget();

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
            sleep();                    //increase energy
            break;
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
    else if (!this->afterReproduction && reproductionPeriod && fullness >= ESSENTIAL_PERCENT_OF_FULLNESS * maxFullness &&
                                                    energy >= ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy)
        target = PARTNER;
    else if (this->afterReproduction && fullness >= ESSENTIAL_PERCENT_OF_FULLNESS * maxFullness &&
                                        energy >= ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy)
        target = SLEEP;
    else if (fullness < ESSENTIAL_PERCENT_OF_FULLNESS * maxFullness)
        target = FOOD;
    else if (energy < ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy)
        target = SLEEP;
    else if (fullness < TEMPERATE_PERCENT_OF_FULLNESS * maxFullness)
        target = FOOD;
    else if (energy < ESSENTIAL_PERCENT_OF_ENERGY * maxEnergy &&
                                            fullness > SUFFICIENT_PERCENT_OF_FULLNESS * maxFullness)
        target = SLEEP;
    else
        target = FOOD;
    return target;
}

void Animal::eat(Coordinates &targetPosition, Coordinates &consumedSubjectPosition) {
    this->fullness = this->maxFullness;
    consumedSubjectPosition = targetPosition;
}

void Animal::sleep() {
    energy += PERCENT_OF_REGENERATION * maxEnergy;
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

bool Animal::oneLeapMove(AreaMap &areaMap, Coordinates targetPosition, Target target) { // if targetPosition = (-1, -1) -> there is no target
    Coordinates currentPosition = make_pair(this->position.first, this->position.second);
    vector<Coordinates> freePositions = areaMap.returnFreeAdjacentPositions(currentPosition);
    if (freePositions.empty())
        return false;                                  //adjacent positions are occupied
    if (targetPosition == make_pair(-1, -1)) targetPosition = this->defaultTarget;
        
    Coordinates nextPos;
    if (target == PARTNER || target == FOOD) {
        nextPos = countDistancesFromTarget(targetPosition, freePositions, true);
    } else if (target == ESCAPE) {
        nextPos = countDistancesFromTarget(targetPosition, freePositions, false);
    }
    this->position = nextPos;
    
    if (this->position == this->defaultTarget)
    {
        defaultTarget = changeDefaultTarget(defaultTarget);
    }

    //change animal position (in areaMap too):
    auto it = areaMap.find(currentPosition);
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
    fullness -= ((float)digestionRate / AnimalConstants::NUMBER_OF_PERCENTS) * maxFullness;
    if (fullness < AnimalConstants::ZERO_FULLNESS)
        fullness = AnimalConstants::ZERO_FULLNESS;
    energy -= leapsNumber;
    if (energy < AnimalConstants::ZERO_ENERGY)
        energy = AnimalConstants::ZERO_ENERGY;
    lifeTime++;
}

//helpers
int Animal::generateMaxEnergy() {
    return (rand() % AnimalConstants::SIZEOF_MAX_ENERGY_RANGE + AnimalConstants::MIN_MAX_ENERGY);
}

int Animal::generateMaxFullness() {
    if (this->type == HERBIVORE){
        return (rand() % AnimalConstants::SIZEOF_MAX_FULLNESS_RANGE + AnimalConstants::MIN_MAX_FULLNESS);}
    if(this->type == PREDATOR ){
        return (rand() % AnimalConstants::SIZEOF_MAX_FULLNESS_RANGE + 2*AnimalConstants::MIN_MAX_FULLNESS);}
    return (rand() % AnimalConstants::SIZEOF_MAX_FULLNESS_RANGE + AnimalConstants::MIN_MAX_FULLNESS);

}

int Animal::generateVelocity() {
    if (type == HERBIVORE)
        return (rand() % AnimalConstants::SIZEOF_VELOCITY_RANGE_HERBIVORE + AnimalConstants::MIN_VELOCITY_HERBIVORE);
    if (type == PREDATOR)
        return (rand() % AnimalConstants::SIZEOF_VELOCITY_RANGE_PREDATOR + AnimalConstants::MIN_VELOCITY_PREDATOR);
    return (rand() % AnimalConstants::SIZEOF_VELOCITY_RANGE_HERBIVORE + AnimalConstants::MIN_VELOCITY_HERBIVORE);
}

int Animal::generateDigestionRate() {
    return (rand() % AnimalConstants::SIZEOF_DIGESTION_RATE_RANGE + AnimalConstants::MIN_DIGESTION_RATE);
}

Coordinates Animal::generateDefaultTarget() {
    int LeftRight = rand()%2;
    int UpDown = rand()%2;
    int x, y;
    if (LeftRight == 0) x = 0;
    else x = (WINDOW_WIDTH/AREA_SIZE)-1;
    if (UpDown == 0) y = 0;
    else y = (WINDOW_HEIGHT/AREA_SIZE)-1;

    Coordinates res = make_pair(x, y);
    return res;
}

Coordinates Animal::changeDefaultTarget(Coordinates actualTarget)
{
    int x, y;
    if (actualTarget.first == 0)
    { x = (WINDOW_WIDTH/AREA_SIZE)-1;}
    else 
    { x = 0;}

    if (actualTarget.second == 0) 
    {y = (WINDOW_HEIGHT/AREA_SIZE)-1;}
    else 
    {y = 0;}
    Coordinates res = make_pair(x, y);
    return res;
}

int Animal::countChildAttribute(int firstParentAttr, int secondParentAttr) const {
    return (int)round((firstParentAttr + secondParentAttr) / AnimalConstants::PARENTS_NUMBER);
}

bool Animal::isMutation() {
    return rand() % AnimalConstants::MUTATIONS_FREQUENCY == AnimalConstants::MUTATION_OCCURRING_CONDITION;
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
int Animal::getVelocity() const { return this->velocity; }
int Animal::getDigestionRate() const { return this->digestionRate; }
int Animal::getMaxEnergy() const { return this->maxEnergy; }
int Animal::getMaxFullness() const { return this->maxFullness; }

//setters
void Animal::setFullness(int newFullness) { fullness = newFullness; }
//void Animal::setLifeTime(int newLifeTme) { lifeTime = newLifeTime; }
void Animal::setEnergy(int newEnergy) { energy = newEnergy; }
void Animal::setVelocity(int newVelocity) { velocity = newVelocity; }
void Animal::setDigestionRate(int newDigestionRate) { digestionRate = newDigestionRate; }
void Animal::setMaxEnergy(int newMaxEnergy) { maxEnergy = newMaxEnergy; }
void Animal::setMaxFullness(int newMaxFullness) { maxFullness = newMaxFullness; }
void Animal::setFlagAfterReproduction() { afterReproduction = true; }


void Animal::printInfo()
{
    cout << "Energy: " << energy << endl;
    cout << "Fullness: " << fullness << endl;
    cout << "Life Time: " << lifeTime << endl;
    cout << "Velocity: " << velocity << endl;
    cout << "Digestion rate: " << digestionRate << endl;
    cout << "VIew Size: " << viewSize << endl; 
}