//Andrzej Przybylski & Monika Berlinska
//Factory to create new subjects
#ifndef SUBJECTSFACTORY_HPP
#define SUBJECTSFACTORY_HPP
#include <stdio.h>
#include <exception>
#include <cstdlib>
#include <ctime>
#include "Plant.hpp"
#include "Herbivore.hpp"
#include "Predator.hpp"

class SubjectsFactory {
    private:
        enum {PREDATOR, HERBIVORE, PLANT};
        SubjectsFactory() { srand(time(NULL)); }
        SubjectsFactory(const SubjectsFactory&) = delete;
        SubjectsFactory& operator=(const SubjectsFactory&) = delete;
    
    public:
        static SubjectsFactory& getInstance(){
            static SubjectsFactory instance;
            return instance;
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
                    sub = new Predator(x, y);
                    break;
                case HERBIVORE: 
                    sub = new Herbivore(x, y);
                    break;
                case PLANT:
                    sub = new Plant(x, y);
                    break;
                default:
                   throw exc;
            }
            return sub;
        }
};

#endif