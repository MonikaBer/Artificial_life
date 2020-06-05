//Andrzej Przybylski & Monika Berlinska
//accessory types and functions
#ifndef HELPER_HPP
#define HELPER_HPP
#include <utility>
#include <vector>


typedef std::pair<int, int> Coordinates;

std::vector<float> countDistancesFromTarget(Coordinates targetPosition, std::vector<Coordinates> freePositions);
extern int AREA_SIZE;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int ONE_CYCLE_SIZE;
extern int SIMULATION_SPEED;             //number between 1 and 100
extern int DELAY_TIME;

extern int REPRODUCTION_FREQUENCY;       //break between reproduction periods
extern int REPRODUCTION_PERIOD_LENGTH;    

//starting number of subjects:
extern int NUMBER_OF_TYPICAL_PLANTS;
extern int NUMBER_OF_HERBIVORES;
extern int NUMBER_OF_PREDATORS;
extern int MAX_LIFE_TIME;
extern int VIEW_SIZE;


#endif
