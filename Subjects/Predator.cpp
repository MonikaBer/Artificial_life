//Andrzej Przybylski & Monika Berlinska
//class representing predator animals
#include"Predator.hpp"


Predator::Predator(int x, int y, int maxLifeTimeSetting, int viewSizeSetting) : 
  Animal(x, y, maxLifeTimeSetting, viewSizeSetting) {}

void Predator::eat(Subject &eaten) {
    
    printf("eating virtual fun");
}