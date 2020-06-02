//Andrzej Przybylski & Monika Berlinska
//Base class for all kind of creatures living in artificial world
#ifndef SUBJECT_HPP
#define SUBJECT_HPP

class Subject {
    protected:
        int xposition;
        int yposition;
        bool toDelete;  //is (or not) subject to delete
    
    public:
        Subject(int x, int y)
        {
            xposition = x;
            yposition = y;
            toDelete = false;
        }

        virtual ~Subject(){}
        
        int getXPosition()
        {
            return xposition;
        }
        
        int getYPosition()
        {
            return yposition;
        }

        bool isToDelete() {
            return toDelete;
        }
};

#endif