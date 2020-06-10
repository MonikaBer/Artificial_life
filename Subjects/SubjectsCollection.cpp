//Andrzej Przybylski & Monika Berlinska
//container for all kind of subjects
#include "SubjectsCollection.hpp"

using namespace std;

bool SubjectsCollection::push(Plant *sub)
{
    Coordinates tmpPair = make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert(tmpPair, sub);
        this->plantsCollection.push_back(sub);
        return true;  //success - plant added
    }
    return false;  //fail - on this position exists another plant
}

bool SubjectsCollection::push(Herbivore *sub)
{
    Coordinates tmpPair = make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert(tmpPair, sub);
        this->herbivoresCollection.push_back(sub);
        return true;  //success - herbivore added
    }
    return false;  //fail - on this position exists another herbivore
}

bool SubjectsCollection::push(Predator *sub)
{
    Coordinates tmpPair = make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert(tmpPair, sub);
        this->predatorsCollection.push_back(sub);
        return true;  //success - predator added
    }
    return false;  //fail - on this position exists another predator
}

void SubjectsCollection::actualizeSubjectsPositionOnScreen(MainWindow* mainWindow)
{
    vector<Plant*>::iterator plantIter;
    vector<Herbivore*>::iterator herbIter;
    vector<Predator*>::iterator predIter;

    for (plantIter = plantsCollection.begin(); plantIter != plantsCollection.end(); ++plantIter) {
        mainWindow->drawTypicalPlant((*plantIter)->getXPosition(), (*plantIter)->getYPosition());
    }
    for (herbIter = herbivoresCollection.begin(); herbIter != herbivoresCollection.end(); ++herbIter) { 
        mainWindow->drawHerbivore((*herbIter)->getXPosition(), (*herbIter)->getYPosition());
    }
    for (predIter = predatorsCollection.begin(); predIter  != predatorsCollection.end(); ++predIter)  { 
        mainWindow->drawPredator((*predIter)->getXPosition(), (*predIter)->getYPosition());
    }
}

void SubjectsCollection::deleteAllSubjects()
{
    auto it = this->areaMap.begin();

    for (; it != this->areaMap.end(); it++)
    {
        delete (*it).second;
    }
    areaMap.clear();
    plantsCollection.clear();
    herbivoresCollection.clear();
    predatorsCollection.clear();
}

void SubjectsCollection::deletePredator(int predIndex) {
    Coordinates predPosition = make_pair(predatorsCollection[predIndex]->getXPosition(),
                                         predatorsCollection[predIndex]->getYPosition());
    //delete from collection
    predatorsCollection.erase(predatorsCollection.begin() + predIndex);
    //delete from map
    auto it = areaMap.find(predPosition);
    delete (*it).second;
    //delete from map
    areaMap.erase(it);
}

void SubjectsCollection::deleteHerbivore(int herbIndex) {
    Coordinates herbPosition = make_pair(herbivoresCollection[herbIndex]->getXPosition(),
                                         herbivoresCollection[herbIndex]->getYPosition());
    //delete from collection
    herbivoresCollection.erase(herbivoresCollection.begin() + herbIndex);
    //delete from map
    auto it = areaMap.find(herbPosition);
    delete (*it).second;
    //delete from map
    areaMap.erase(it);
}

void SubjectsCollection::deleteHerbivore(Coordinates herbPosition) {
    auto it = areaMap.find(herbPosition);
    //delete from collection
    for (auto herbIter = herbivoresCollection.begin();
         herbIter != herbivoresCollection.end(); herbIter++) {
        if ((*herbIter)->getXPosition() == herbPosition.first && (*herbIter)->getYPosition() == herbPosition.second) {
            herbivoresCollection.erase(herbIter);
            break;
        }
    }
    delete (*it).second;
    //delete from map
    areaMap.erase(it);
}

//void SubjectsCollection::deletePlant(int plantIndex) {
//    Coordinates plantPosition = make_pair(plantsCollection[plantIndex]->getXPosition(),
//                                         plantsCollection[plantIndex]->getYPosition());
//    //delete from collection
//    plantsCollection.erase(plantsCollection.begin() + plantIndex);
//    map<Coordinates, Subject*>::iterator it = areaMap.find(plantPosition);
    //   delete (*it).second;
    //   delete from map
//    areaMap.erase(it);
//}

void SubjectsCollection::deletePlant(Coordinates plantPosition) {
    auto it = areaMap.find(plantPosition);
    //delete from collection
    for (auto plantIter = plantsCollection.begin(); plantIter != plantsCollection.end(); plantIter++) {
        if ((*plantIter)->getXPosition() == plantPosition.first && (*plantIter)->getYPosition() == plantPosition.second) {
            plantsCollection.erase(plantIter);
            break;
        }
    }
    delete (*it).second;
    //delete from map
    areaMap.erase(it);
}

void SubjectsCollection::subjectsRound(bool reproductionPeriod, int maxLifeTime, int viewSize)
{
    Coordinates partnerPosition = make_pair(-1, -1);
    Coordinates consumedSubjectPosition = make_pair(-1, -1);
    Coordinates childPosition = make_pair(-1, -1);
    map<Coordinates, Subject*>::iterator parent1;
    map<Coordinates, Subject*>::iterator parent2;

    for (int predIndex = 0; predIndex != predatorsCollection.size(); predIndex++) {
        predatorsCollection[predIndex]->thisTurn(areaMap, reproductionPeriod, partnerPosition, consumedSubjectPosition, childPosition);
        if (predatorsCollection[predIndex]->isToDelete()) {
            deletePredator(predIndex);
            predIndex--;
            continue;
        }
        if (consumedSubjectPosition.first != -1 && consumedSubjectPosition.second != -1){ //some herbivore was consumed
            deleteHerbivore(consumedSubjectPosition);
        }
        if (childPosition.first != -1 && childPosition.second != -1) {
            //add child to areaMap and to predatorsCollection
            auto *predatorChild = new Predator(childPosition.first, childPosition.second, maxLifeTime, viewSize);
            parent1 = areaMap.find(predatorsCollection[predIndex]->getPosition());
            parent2 = areaMap.find(partnerPosition);
            predatorChild->mixAttributes(dynamic_cast<Animal*>(parent1->second), dynamic_cast<Animal*>(parent2->second));
            this->push(predatorChild);
        }
        partnerPosition.first = -1;
        partnerPosition.second = -1;
        consumedSubjectPosition.first = -1;
        consumedSubjectPosition.second = -1;
        childPosition.first = -1;
        childPosition.second = -1;
    }

    for (int herbIndex = 0; herbIndex != herbivoresCollection.size(); herbIndex++) {
        herbivoresCollection[herbIndex]->thisTurn(areaMap, reproductionPeriod,  partnerPosition, consumedSubjectPosition, childPosition);
        if (herbivoresCollection[herbIndex]->isToDelete()) {
            deleteHerbivore(herbIndex);
            herbIndex--;
            continue;
        }
        if (consumedSubjectPosition.first != -1 && consumedSubjectPosition.second != -1){ //some plant was consumed
            deletePlant(consumedSubjectPosition);
        }
        if (childPosition.first != -1 && childPosition.second != -1) {
            //add child to areaMap and to herbivoresCollection
            auto *herbivoreChild = new Herbivore(childPosition.first, childPosition.second, maxLifeTime, viewSize);
            this->push(herbivoreChild);
        }
        partnerPosition.first = -1;
        partnerPosition.second = -1;
        consumedSubjectPosition.first = -1;
        consumedSubjectPosition.second = -1;
        childPosition.first = -1;
        childPosition.second = -1;
    }
}

//getters
int SubjectsCollection::getPlantsNumber() {
    return plantsCollection.size();
}

int SubjectsCollection::getHerbivoresNumber() {
    return herbivoresCollection.size();
}

int SubjectsCollection::getPredatorsNumber() {
    return predatorsCollection.size();
}
//setters
void SubjectsCollection::setSizeOfAreaMap(int newWidth, int newHeight) {
    areaMap.setSize(newWidth, newHeight);
}

void SubjectsCollection::getSubjectInfoFromPosition(Coordinates pos)
{
    Subject *tmp = nullptr;
    int x, y;
    x = pos.first;
    y = pos.second;
    std::map<Coordinates, Subject*>::iterator it;
    for (it = areaMap.begin(); it!= areaMap.end(); ++it)
    {
        if ((*it).first.first == x && (*it).first.second == y)
        {
            tmp = (*it).second;
            break;
        }
    }
    if (tmp != nullptr)
    {
        switch(tmp->getType())
        {
            case PREDATOR:
                cout << "Predator" << endl;
                dynamic_cast<Animal*>(tmp)->printInfo();
                cout << endl;
                break;
            case HERBIVORE:
                cout << "Herbivore" << endl;
                dynamic_cast<Animal*>(tmp)->printInfo();
                cout << endl;
                break;
            case TYPICAL_PLANT:
                cout << "Typical plant" << endl;
                cout << endl;
            case SUPER_PLANT:
                cout << "Super plant" << endl;
                cout << endl;
        }
    }
    tmp = nullptr;
}