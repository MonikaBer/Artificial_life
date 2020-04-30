//Andrzej Przybylski & Monika Berlinska
//class representing predator animals
#include"Predator.hpp"


Predator::Predator(int x, int y) : Animal(x, y) {
    
}

void Predator::eat(Subject &eaten) {
    
    printf("eating virtual fun");
}