//Andrzej Przybylski & Monika Berlinska
//container for all kind of subjects
#include "SubjectsCollection.hpp"

bool SubjectsCollection::push(Plant *sub)
{
    Coordinates tmpPair = std::make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert({tmpPair, sub});
        this->plantsCollection.push_back(sub);
        return true;  //success - plant added
    }
    return false;  //fail - on this position exists another plant
}

bool SubjectsCollection::push(Herbivore *sub)
{
    Coordinates tmpPair = std::make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert({tmpPair, sub});
        this->herbivoresCollection.push_back(sub);
        return true;  //success - herbivore added
    }
    return false;  //fail - on this position exists another herbivore
}

bool SubjectsCollection::push(Predator *sub)
{
    Coordinates tmpPair = std::make_pair(sub->getXPosition(), sub->getYPosition());
    if (areaMap.count(tmpPair) == 0){
        this->areaMap.insert({tmpPair, sub});
        this->predatorsCollection.push_back(sub);
        return true;  //success - predator added
    }
    return false;  //fail - on this position exists another predator
}

void SubjectsCollection::actualizeSubjectsPositionOnScreen(MainWindow* mainWindow)
{
    std::vector<Plant*>::iterator plantIter;
    std::vector<Herbivore*>::iterator herbIter;
    std::vector<Predator*>::iterator predIter;

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
    std::map<Coordinates, Subject*>::iterator it = this->areaMap.begin();

    for (it; it != this->areaMap.end(); it++) 
    {
        delete (*it).second;
    }
    areaMap.clear();
    plantsCollection.clear();
    herbivoresCollection.clear();
    predatorsCollection.clear();
}

void SubjectsCollection::subjectsRound(bool reproductionPeriod)
{
    std::vector<Predator*>::iterator predIter;
    std::vector<Herbivore*>::iterator herbIter;
    for (predIter = predatorsCollection.begin(), herbIter = herbivoresCollection.begin(); ; )
    {
        if (predIter != predatorsCollection.end()) {
            (*predIter)->thisTurn(reproductionPeriod);
            predIter++;
        }
        if (herbIter != herbivoresCollection.end()) {
            (*herbIter)->thisTurn(reproductionPeriod);
            herbIter++;
        }
        if (predIter == predatorsCollection.end() && herbIter == herbivoresCollection.end())
            return;
    }
}