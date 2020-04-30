//Andrzej Przybylski & Monika Berlinska
//class representing herbivore animals
#include"Herbivore.hpp"


Herbivore::Herbivore(int x, int y) : Animal(x, y) {
    
}

void Herbivore::eat(Subject &eaten) {
    
    printf("eating virtual fun");
}