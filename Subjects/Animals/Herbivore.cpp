//Andrzej Przybylski & Monika Berlinska
//class representing herbivore animals
#include <map>
#include "Herbivore.hpp"

using namespace std;

Herbivore::Herbivore(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : 
  Animal(x, y, maxLifeTimeSetting, viewSizeSetting) {
    caloricity = 1.0;
    type = HERBIVORE;
}

bool Herbivore::lookAround(AreaMap &areaMap, Coordinates &targetPosition, Target &target, bool reproductionPeriod) {
//    bool isTargetEncountered = false;
//
//    for (map<Coordinates, Subject*>::iterator it = areaMap.begin(); it != areaMap.end(); ++it) {
//        if (it->second->getType() == PREDATOR) {
//            if (!reproductionPeriod && this->isVisibleForAnimal(it->first)) {
//                targetPosition.first = it->first.first;
//                targetPosition.second = it->first.second;
//                target = ESCAPE;
//                return false;
//            }
//        } else if (it->second->getType() == HERBIVORE && target == PARTNER) {
//            if (isTargetEncountered)
//                continue;
//            if (this->isVisibleForAnimal(it->first)) {
//                targetPosition.first = it->first.first;
//                targetPosition.second = it->first.second;
//                if (this->isEncountered(it->first))
//                    isTargetEncountered = true;
//            }
//        } else if ((it->second->getType() == TYPICAL_PLANT || it->second->getType() == SUPER_PLANT) && target == FOOD) {
//            if (isTargetEncountered)
//                continue;
//            if (this->isVisibleForAnimal(it->first)) {
//                targetPosition.first = it->first.first;
//                targetPosition.second = it->first.second;
//                if (this->isEncountered(it->first))
//                    isTargetEncountered = true;
//            }
//        }
//    }
//
//    if (isTargetEncountered)
//        return true;
//
//    if (target == NEUTRAL || target == SLEEP)
//        return false;
//
//    return false;  //target is encountered
    return false;
}