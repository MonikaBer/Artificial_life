//Andrzej Przybylski & Monika Berlinska
//class representing herbivore animals
#include "Herbivore.hpp"


Herbivore::Herbivore(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : 
  Animal(x, y, maxLifeTimeSetting, viewSizeSetting) {
    caloricity = 1.0;
    type = HERBIVORE;      
}

bool Herbivore::lookAround(const AreaMap &areaMap, Coordinates &targetPosition, Target &target) {

    return true;  //target is encountered
}