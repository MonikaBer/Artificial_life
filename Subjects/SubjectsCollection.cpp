//Andrzej Przybylski & Monika Berlinska
//container for all kind of subjects
#include "SubjectsCollection.hpp"

using namespace std;

bool SubjectsCollection::push(Plant *sub)
{
    Coordinates tmpPair = make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert({tmpPair, sub});
        this->plantsCollection.push_back(sub);
        return true;  //success - plant added
    }
    return false;  //fail - on this position exists another plant
}

bool SubjectsCollection::push(Herbivore *sub)
{
    Coordinates tmpPair = make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert({tmpPair, sub});
        this->herbivoresCollection.push_back(sub);
        return true;  //success - herbivore added
    }
    return false;  //fail - on this position exists another herbivore
}

bool SubjectsCollection::push(Predator *sub)
{
    Coordinates tmpPair = make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert({tmpPair, sub});
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
    map<Coordinates, Subject*>::iterator it = this->areaMap.begin();

    for (it; it != this->areaMap.end(); it++) 
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
    map<Coordinates, Subject*>::iterator it = areaMap.find(predPosition);
    delete (*it).second;
    areaMap.erase(it);
}

void SubjectsCollection::deleteHerbivore(int herbIndex) {
    Coordinates herbPosition = make_pair(herbivoresCollection[herbIndex]->getXPosition(),
                                         herbivoresCollection[herbIndex]->getYPosition());
    //delete from collection
    herbivoresCollection.erase(herbivoresCollection.begin() + herbIndex);
    //delete from map
    map<Coordinates, Subject*>::iterator it = areaMap.find(herbPosition);
    delete (*it).second;
    areaMap.erase(it);
}

void SubjectsCollection::deleteHerbivore(Coordinates herbPosition) {
    map<Coordinates, Subject*>::iterator it = areaMap.find(herbPosition);
    //delete from collection
    for (vector<Herbivore*>::iterator herbIter = herbivoresCollection.begin();
         herbIter != herbivoresCollection.end(); herbIter++) {
        if ((*herbIter)->getXPosition() == herbPosition.first && (*herbIter)->getYPosition() == herbPosition.second) {
            herbivoresCollection.erase(herbIter);
            break;
        }
    }
    //delete from map
    delete (*it).second;
    areaMap.erase(it);
}

//void SubjectsCollection::deletePlant(int plantIndex) {
//    Coordinates plantPosition = make_pair(plantsCollection[plantIndex]->getXPosition(),
//                                         plantsCollection[plantIndex]->getYPosition());
//    //delete from collection
//    plantsCollection.erase(plantsCollection.begin() + plantIndex);
//    //delete from map
//    map<Coordinates, Subject*>::iterator it = areaMap.find(plantPosition);
//    delete (*it).second;
//    areaMap.erase(it);
//}

void SubjectsCollection::deletePlant(Coordinates plantPosition) {
    map<Coordinates, Subject*>::iterator it = areaMap.find(plantPosition);
    //delete from collection
    for (vector<Plant*>::iterator plantIter = plantsCollection.begin();
         plantIter != plantsCollection.end(); plantIter++) {
        if ((*plantIter)->getXPosition() == plantPosition.first && (*plantIter)->getYPosition() == plantPosition.second) {
            plantsCollection.erase(plantIter);
            break;
        }
    }
    //delete from map
    delete (*it).second;
    areaMap.erase(it);
}

void SubjectsCollection::subjectsRound(bool reproductionPeriod)
{
    Coordinates consumedSubjectPosition = make_pair(-1, -1);
    Coordinates childPosition = make_pair(-1, -1);

    for (int predIndex = 0; predIndex != predatorsCollection.size(); predIndex++) {
        predatorsCollection[predIndex]->thisTurn(reproductionPeriod, consumedSubjectPosition, childPosition);
        if (predatorsCollection[predIndex]->isToDelete()) {
            deletePredator(predIndex);
            predIndex--;
            continue;
        }
        if (consumedSubjectPosition.first != -1 && consumedSubjectPosition.second != -1){ //some herbivore was consumed
            deleteHerbivore(consumedSubjectPosition);
            consumedSubjectPosition.first = -1;
            consumedSubjectPosition.second = -1;
        }
        if (childPosition.first != -1 && childPosition.second != -1) {
            //add child to areaMap and to predatorsCollection
        }
    }

    for (int herbIndex = 0; herbIndex != herbivoresCollection.size(); herbIndex++) {
        herbivoresCollection[herbIndex]->thisTurn(reproductionPeriod, consumedSubjectPosition, childPosition);
        if (herbivoresCollection[herbIndex]->isToDelete()) {
            deleteHerbivore(herbIndex);
            herbIndex--;
            continue;
        }
        if (consumedSubjectPosition.first != -1 && consumedSubjectPosition.second != -1){ //some plant was consumed
            deletePlant(consumedSubjectPosition);
            consumedSubjectPosition.first = -1;
            consumedSubjectPosition.second = -1;
        }
        if (childPosition.first != -1 && childPosition.second != -1) {
            //add child to areaMap and to herbivoresCollection
        }
    }

    // vector<Predator*>::iterator predIter;
    // vector<Herbivore*>::iterator herbIter;
    // for (predIter = predatorsCollection.begin(), herbIter = herbivoresCollection.begin(); 
        //predIter != predatorsCollection.end() || herbIter != herbivoresCollection.end(); )
    // {
    //     if (predIter != predatorsCollection.end()) {
    //         (*predIter)->thisTurn(reproductionPeriod, animalToDelete, consumedSubjectPosition);
    //         predIter++;
    //     }
    //     if (herbIter != herbivoresCollection.end()) {
    //         (*herbIter)->thisTurn(reproductionPeriod, animalToDelete, consumedSubjectPosition);
    //         herbIter++;
    //     }
}

int SubjectsCollection::getPlantsNumber() {
    return plantsCollection.size();
}