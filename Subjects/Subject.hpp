//Andrzej Przybylski & Monika Berlinska
//Base class for all kind of creatures living in artificial world
#ifndef SUBJECT_HPP
#define SUBJECT_HPP

typedef enum {PREDATOR, HERBIVORE, TYPICAL_PLANT, SUPER_PLANT} SubjectType;

class Subject {
    protected:
        int xPosition;
        int yPosition;
        bool toDelete;  //is (or not) subject to delete
        SubjectType type;
    
    public:
        Subject(int x, int y)
        {
            xPosition = x;
            yPosition = y;
            toDelete = false;
        }

        virtual ~Subject(){}
        
        int getXPosition()
        {
            return xPosition;
        }
        
        int getYPosition()
        {
            return yPosition;
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