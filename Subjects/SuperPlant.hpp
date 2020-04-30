//Andrzej Przybylski & Monika Berlinska
#ifndef SUPER_PLANT_HPP
#define SUPER_PLANT_HPP

class SuperPlant : public Plant {
    public:
        SuperPlant(int x, int y) : Plant(x, y) {
            this.caloricity = 1.0; 
        } 
};

#endif