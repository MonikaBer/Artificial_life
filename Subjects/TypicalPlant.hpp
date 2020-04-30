//Andrzej Przybylski & Monika Berlinska
#ifndef TYPICAL_PLANT_HPP
#define TYPICAL_PLANT_HPP

class TypicalPlant : public Plant { 
    public:
        TypicalPlant(int x, int y) : Plant(x, y) {
            this.caloricity = 0.25; 
        }        
};

#endif