//Andrzej Przybylski & Monika Berlinska
//accessory types and functions
#ifndef HELPER_HPP
#define HELPER_HPP
#include <utility>
#include <vector>


typedef std::pair<int, int> Coordinates;

std::vector<float> countDistancesFromTarget(Coordinates targetPosition, std::vector<Coordinates> freePositions);

#endif
