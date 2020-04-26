//Andrzej Przybylski & Monika Berlinska
//Base class for all kind of creatures living in artificial world

class Subject {
    private:
        int xposition;
        int yposition;
        int velocity;
        int viewrange;
    public:
        Subject(int x, int y, int vel);
        int getXPosition();
        int getYPosition();
        //virtual void move();
};

