//Andrzej Przybylski & Monika Berlinska
//Base class for all kind of creatures living in artificial world
#ifndef SUBJECT_HPP
#define SUBJECT_HPP
#include <utility>
#include "../helper.hpp"

typedef enum {PREDATOR, HERBIVORE, TYPICAL_PLANT, SUPER_PLANT} SubjectType;

class Subject {
    protected:
        Coordinates position;
        bool toDelete;                  //if subject to delete
        SubjectType type;
    
    public:
        Subject(int x, int y)
        {
            position = std::make_pair(x, y);
            toDelete = false;
        }

        virtual ~Subject(){}
        
        int getXPosition()
        {
            return position.first;
        }
        
        int getYPosition()
        {
            return position.second;
        }

        Coordinates getPosition() {
            return position;
        }

        bool isToDelete() {
            return toDelete;
        }

        void setType(SubjectType subType) {
            type = subType;
        }

        SubjectType getType() {
            return type;
        }
};

#endif