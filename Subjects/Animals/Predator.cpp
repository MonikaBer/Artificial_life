//Andrzej Przybylski & Monika Berlinska
//class representing predator animals
#include "Predator.hpp"


Predator::Predator(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : 
  Animal(x, y, maxLifeTimeSetting, viewSizeSetting) {}

bool Predator::lookAround(Coordinates &targetPosition, Target &target) {
    
    return true;  //target is encountered
}