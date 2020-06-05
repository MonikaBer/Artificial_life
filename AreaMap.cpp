//Andrzej Przybylski & Monika Berlinska
//base class for area of subjects' living
#include "AreaMap.hpp"

using namespace std;

void AreaMap::insert(Coordinates position, Subject* sub) {
    subjectsPositions.insert({position, sub});
}

std::map<Coordinates, Subject*>::iterator AreaMap::find(Coordinates position) {
    return subjectsPositions.find(position);
}

int AreaMap::count(Coordinates position) {
    return subjectsPositions.count(position);
}

map<Coordinates, Subject*>::iterator AreaMap::begin() {
    return subjectsPositions.begin();    
}

map<Coordinates, Subject*>::iterator AreaMap::end() {
    return subjectsPositions.end();    
}

void AreaMap::erase(std::map<Coordinates, Subject*>::iterator it) {
    subjectsPositions.erase(it);
}

void AreaMap::clear() {
    subjectsPositions.clear();
}

//getters
map<Coordinates, Subject*> AreaMap::getSubjectsPositions() {
    return subjectsPositions;
}

int AreaMap::getWidth() {
    return width;
}

int AreaMap::getHeight() {
    return height;
}

//setters
void AreaMap::setSize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}