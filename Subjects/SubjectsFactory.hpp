//Andrzej Przybylski & Monika Berlinska
//Factory to create new subjects
#ifndef SUBJECTS_FACTORY_HPP
#define SUBJECTS_FACTORY_HPP
#include <exception>
#include <cstdlib>
#include <ctime>
#include "Plants/TypicalPlant.hpp"
#include "Plants/SuperPlant.hpp"
#include "Animals/Herbivore.hpp"
#include "Animals/Predator.hpp"

class SubjectsFactory {
    private:
        SubjectsFactory() { srand(time(NULL)); }
        SubjectsFactory(const SubjectsFactory&) = delete;
        SubjectsFactory& operator=(const SubjectsFactory&) = delete;
    
    public:
        static SubjectsFactory& getInstance(){
            static SubjectsFactory instance;
            return instance;
        }

        Subject* create(SubjectType type, int maxX, int maxY, int maxLifeTimeSetting, int viewSizeSetting)
        {
            std::exception exc;
            Subject *sub = nullptr;
            int x = std::rand() % maxX;
            int y = std::rand() % maxY;

            switch (type)
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