//Andrzej Przybylski & Monika Berlinska
//class representing predator animals
#include <map>
#include "Predator.hpp"

using namespace std;


Predator::Predator(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : 
  Animal(x, y, maxLifeTimeSetting, viewSizeSetting) {

    type = PREDATOR;
}

bool Predator::lookAround(AreaMap &areaMap, Coordinates &targetPosition, Target &target, bool reproductionPeriod) {
    if (target == NEUTRAL || target == SLEEP) {
        return false;
    }

    for (map<Coordinates, Subject*>::iterator it = areaMap.begin(); it != areaMap.end(); ++it) {
        if (it->second->getType() == PREDATOR && target == PARTNER) {
            if (this->isVisibleForAnimal(it->first)) {
                targetPosition.first = it->first.first;
                targetPosition.second = it->first.second;
                if (this->isEncountered(it->first)) {
                    return true;
                }
            }
        } else if (it->second->getType() == HERBIVORE && target == FOOD) {
            if (this->isVisibleForAnimal(it->first)) {
                targetPosition.first = it->first.first;
                targetPosition.second = it->first.second;
                if (this->isEncountered(it->first)) {
                    return true;
                }
            }
        }
    }

    return !(targetPosition.first == -1 && targetPosition.second == -1);
    //return false;
}