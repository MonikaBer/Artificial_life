//Andrzej Przybylski & Monika Berlinska
//virtual base class for animals
#include "Animal.hpp"
using namespace std;

void Animal::move(){
    
    printf("moving algorithm");
}

void Animal::lookAround() {
    
    printf("Checking if something is in seeing area");
}

void Animal::setDirection(int dir) {
    
    exception ex;
    
    if(dir < 0 || dir > 7)
        throw ex;
    
    this.direction = dir;
}