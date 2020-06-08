//Andrzej Przybylski & Monika Berlinska
//Class with constants for animals
#ifndef ANIMAL_CONSTANTS_HPP
#define ANIMAL_CONSTANTS_HPP

        extern const double PERCENT_OF_REGENERATION = 0.1;
        extern const double ESSENTIAL_PERCENT_OF_ENERGY = 0.2;
        extern const double ESSENTIAL_PERCENT_OF_FULLNESS = 0.2;
        extern const double TEMPERATE_PERCENT_OF_FULLNESS = 0.5;
        extern const double TEMPERATE_PERCENT_OF_ENERGY = 0.3;
        extern const double SUFFICIENT_PERCENT_OF_FULLNESS = 0.85;

class AnimalConstants {
    public:
        static const int SIZEOF_MAX_ENERGY_RANGE = 101;
        static const int MIN_MAX_ENERGY = 50;
        static const int SIZEOF_MAX_FULLNESS_RANGE = 101;    
        static const int MIN_MAX_FULLNESS = 50;    
        static const int SIZEOF_VELOCITY_RANGE = 3;
        static const int MIN_VELOCITY = 1;
        static const int SIZEOF_DIGESTION_RATE_RANGE = 6;    
        static const int MIN_DIGESTION_RATE = 5;
/*
        extern const double PERCENT_OF_REGENERATION = 0.1;
        static const double ESSENTIAL_PERCENT_OF_ENERGY = 0.2;
        static const double ESSENTIAL_PERCENT_OF_FULLNESS = 0.2;
        static const double TEMPERATE_PERCENT_OF_FULLNESS = 0.5;
        static const double TEMPERATE_PERCENT_OF_ENERGY = 0.3;
        static const double SUFFICIENT_PERCENT_OF_FULLNESS = 0.85;
*/
        static const int ZERO_FULLNESS = 0;
        static const int ZERO_ENERGY = 0;
        static const int ZERO_LIFE_TIME = 0;

        static const int MUTATIONS_FREQUENCY = 10;              // probability of mutation equals to 10 %
        static const int MUTATION_OCCURRING_CONDITION = 0;

        static const int PARENTS_NUMBER = 2.0;
        static const int NUMBER_OF_PERCENTS = 100.0;
};

#endif