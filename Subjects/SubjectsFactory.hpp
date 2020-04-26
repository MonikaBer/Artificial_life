//Andrzej Przybylski & Monika Berlinska
//Factory to create new subjects
#include<stdio.h>
#include<exception>
#include <cstdlib>
#include <ctime>
#include "Plant.h"

class SubjectsFactory {
    private:
        enum {PREDATOR, HERBIVORE, PLANT};
    public:
        SubjectsFactory() 
        {
            srand(time(NULL));
        }
        Subject* create(int type, int maxX, int maxY, int areasize)
        {
            std::exception exc;
            Subject *sub = nullptr;
            int x = (std::rand()%maxX)*areasize;
            int y = (std::rand()%maxY)*areasize;

            switch(type)
            {
                case PREDATOR: 
                    printf("Create a predator");
                    break;
                case HERBIVORE: 
                    printf("Create a herbivore");
                    break;
                case PLANT:
                    sub = new Plant(x,y);
                    break;
                default: ;
                   throw exc;
                   break;
            }
            return sub;
        }
};