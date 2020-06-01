//Andrzej Przybylski & Monika Berlinska
//container for all kind of subjects
#ifndef SUBJECTSCOLLECTION_H
#define SUBJECTSCOLLECTION_H

#include "SubjectsFactory.hpp"
#include "../Graphics/MainWindow.hpp"
#include <vector>
#include <map>
#include <utility>

typedef std::pair<int, int> Coordinates;

class SubjectsCollection {
    private:
        std::vector<Plant*> plantsCollection;
        std::vector<Herbivore*> herbivoresCollection;
        std::vector<Predator*> predatorsCollection;
        std::map<Coordinates, Subject*> areaMap;

        SubjectsCollection(){}
        SubjectsCollection(const SubjectsFactory&) = delete;
        SubjectsCollection& operator=(const SubjectsCollection&) = delete;
    public:
        static SubjectsCollection& getInstance(){
            static SubjectsCollection instance;
            return instance;
        }

        void push(Plant* sub);
        void push(Herbivore *sub);
        void push(Predator *sub);
        void remove(Subject* sub);
        void actualizeSubjectsPositionOnScreen(MainWindow* mainWindow);
        void subjectsRound(int cycleNumber, bool reproductionPeriod);

        void deleteAllSubjects();
};

#endif