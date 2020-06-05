//Andrzej Przybylski & Monika Berlinska
//accessory types and functions
#include <math.h>
#include "helper.hpp"

using namespace std;


vector<float> countDistancesFromTarget(Coordinates targetPosition, vector<Coordinates> freePositions) {
    std::vector<float> distances;
    float distance;
    vector<Coordinates>::iterator it;
    for (it = freePositions.begin(); it != freePositions.end(); ++it) {
        distance = sqrt((pow(targetPosition.first-(*it).first, 2) + pow(targetPosition.second-(*it).second, 2)));
        distances.push_back(distance);
    }
    return distances;
}