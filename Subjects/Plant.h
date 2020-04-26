//Andrzej Przybylski & Monika Berlinska
//Class for plants
#include"Subject.h"

class Plant : public Subject{
    public:
        Plant(int x, int y) : Subject(x, y, 0) {};
};