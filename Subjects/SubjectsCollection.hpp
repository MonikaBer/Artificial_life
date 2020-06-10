//Andrzej Przybylski & Monika Berlinska
//container for all kind of subjects
#ifndef SUBJECTS_COLLECTION_H
#define SUBJECTS_COLLECTION_H

#include "SubjectsFactory.hpp"
#include "../Graphics/MainWindow.hpp"
#include "../AreaMap.hpp"
#include "Animals/Animal.hpp"
#include <vector>

class SubjectsCollection {
    private:
        std::vector<Plant*> plantsCollection;
        std::vector<Herbivore*> herbivoresCollection;
        std::vector<Predator*> predatorsCollection;
        AreaMap areaMap;

        SubjectsCollection() {AreaMap &areaMap = AreaMap::getInstance();}
        SubjectsCollection(const SubjectsFactory&) = delete;
        SubjectsCollection& operator=(const SubjectsCollection&) = delete;
    public:
        static SubjectsCollection& getInstance(){
            static SubjectsCollection instance;
            return instance;
        }

        bool push(Plant* sub);
        bool push(Herbivore *sub);
        bool push(Predator *sub);
        void actualizeSubjectsPositionOnScreen(MainWindow* mainWindow);
        void deleteAllSubjects();
        //void remove(Subject* sub);
        void deletePredator(int predIndex);
        void deleteHerbivore(int herbIndex);
        void deleteHerbivore(Coordinates herbPosition);
        //void delete Plant(int plantIndex);
        void deletePlant(Coordinates plantPosition);
        void subjectsRound(bool reproductionPeriod, int maxLifeTime, int viewSize);
        
        void getSubjectInfoFromPosition(Coordinates pos);
        //getters
        int getPlantsNumber();
        int getHerbivoresNumber();
        int getPredatorsNumber();

        //setters
        void setSizeOfAreaMap(int newWidth, int newHeight);
    };

#endif