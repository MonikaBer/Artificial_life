//Andrzej Przybylski & Monika Berlinska
//base class for area of subjects' living
#include "AreaMap.hpp"

using namespace std;

vector<Coordinates> AreaMap::returnFreeAdjacentPositions(Coordinates position) {
    vector<Coordinates> freePositions;
    map<Coordinates, Subject*>::iterator it;
    Coordinates checkedPosition = make_pair(-1, -1);

    for (checkedPosition.first = position.first-10; checkedPosition.first <= position.first+10; ++checkedPosition.first) {
        for (checkedPosition.second = position.second-10; checkedPosition.second <= position.second+10; ++checkedPosition.second) {
            if (checkedPosition.first == position.first && checkedPosition.second == position.second)
                continue;
            it = this->find(checkedPosition);
            if (it == this->end() && !this->isProhibitedPosition(checkedPosition))  //checkedPosition is free
                freePositions.push_back(checkedPosition);
        }
    }
    return freePositions;
}

bool AreaMap::isProhibitedPosition(Coordinates checkedPosition) {
    return checkedPosition.first < 0 || checkedPosition.second < 0 || checkedPosition.first >= this->width * 10 ||
           checkedPosition.second >= this->height * 10;
}

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
map<Coordinates, Subject*> AreaMap::getSubjectsPositions() const {
    return subjectsPositions;
}

int AreaMap::getWidth() const {
    return width;
}

int AreaMap::getHeight() const {
    return height;
}

//setters
void AreaMap::setSize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}