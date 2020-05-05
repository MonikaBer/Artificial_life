//Andrzej Przybylski & Monika Berlinska
//Factory to create new subjects
#ifndef SUBJECTSFACTORY_HPP
#define SUBJECTSFACTORY_HPP
#include <exception>
#include <cstdlib>
#include <ctime>
#include "Plants/TypicalPlant.hpp"
#include "Plants/SuperPlant.hpp"
#include "Animals/Herbivore.hpp"
#include "Animals/Predator.hpp"

class SubjectsFactory {
    private:
        enum {PREDATOR, HERBIVORE, TYPICAL_PLANT, SUPER_PLANT};
        SubjectsFactory() { srand(time(NULL)); }
        SubjectsFactory(const SubjectsFactory&) = delete;
        SubjectsFactory& operator=(const SubjectsFactory&) = delete;
    
    public:
        static SubjectsFactory& getInstance(){
            static SubjectsFactory instance;
            return instance;
        }

        Subject* create(int type, int maxX, int maxY, int areaSize, int maxLifeTimeSetting, int viewSizeSetting)
        {
            std::exception exc;
            Subject *sub = nullptr;
            int x = (std::rand() % maxX) * areaSize;
            int y = (std::rand() % maxY) * areaSize;

            switch(type)
            {
                case PREDATOR: 
                    sub = new Predator(x, y, maxLifeTimeSetting, viewSizeSetting);
                    break;
                case HERBIVORE: 
                    sub = new Herbivore(x, y, maxLifeTimeSetting, viewSizeSetting);
                    break;
                case TYPICAL_PLANT:
                    sub = new TypicalPlant(x, y);
                    break;
                case SUPER_PLANT:
                    sub = new SuperPlant(x, y);
                    break;
                default:
                   throw exc;
            }
            return sub;
        }
};

#endif