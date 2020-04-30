//Andrzej Przybylski & Monika Berlinska
//Base class for all kind of creatures living in artificial world
#ifndef SUBJECT_H
#define SUBJECT_H

class Subject {
    private:
        int xposition;
        int yposition;
    public:
        Subject(int x, int y)
        {
            xposition = x;
            yposition = y;
        }
        virtual ~Subject(){};
        int getXPosition()
        {
            return xposition;
        }
        int getYPosition()
        {
            return yposition;
        }
        //virtual void move();
};

#endif