//Andrzej Przybylski & Monika Berlinska
//class representing herbivore animals
#include "Herbivore.hpp"


Herbivore::Herbivore(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : 
  Animal(x, y, maxLifeTimeSetting, viewSizeSetting) {
    caloricity = 1.0;      
}

bool Herbivore::lookAround(Coordinates &targetPosition, Target &target) {

    return true;  //target is encountered
}