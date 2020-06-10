//Andrzej Przybylski & Monika Berlinska
//accessory types and functions
#include <cmath>
#include <iostream>
#include "helper.hpp"

using namespace std;


Coordinates countDistancesFromTarget(Coordinates targetPosition, vector<Coordinates> freePositions, bool Minimalize) {
    std::vector<float> distances;
    float distance;
    float distanceMin = WINDOW_WIDTH;
    float distanceMax = -1;
    vector<Coordinates>::iterator it;
    Coordinates coordMin;
    Coordinates coordMax;
    for (it = freePositions.begin(); it != freePositions.end(); ++it) {
        cout << "Free positions coordinates: " << it->first << " " << it->second << endl;
        distance = sqrt((pow(targetPosition.first-(*it).first, 2) + pow(targetPosition.second-(*it).second, 2)));
        if (distance > distanceMax)
        {
            distanceMax = distance;
            coordMax = (*it);
        }
        if (distance < distanceMin)
        {
            distanceMin = distance;
            coordMin = (*it);
        }
    }
    if (Minimalize)
        return coordMin;
    else return coordMax;
}
