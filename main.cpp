#include <iostream>
#include <vector>
#include "Subjects/SubjectsCollection.hpp"

using namespace std;

static const int AREA_SIZE = 5;
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

static const int ONE_CYCLE_SIZE = 100;
static const int SIMULATION_SPEED = 10;             //number between 1 and 100
static const int DELAY_TIME = 1000/SIMULATION_SPEED;

static const int REPRODUCTION_FREQUENCY = 50;       //break between reproduction periods
static const int REPRODUCTION_PERIOD_LENGTH = 10;    

//starting number of subjects:
static const int NUMBER_OF_TYPICAL_PLANTS = 40;
static const int NUMBER_OF_HERBIVORES = 10;
static const int NUMBER_OF_PREDATORS = 5;
static const int MAX_LIFE_TIME = 250;
static const int VIEW_SIZE = 100;

int main()
{
    MainWindow *mainWindow;
    mainWindow = mainWindow->getInstance (WINDOW_WIDTH, WINDOW_HEIGHT, AREA_SIZE, "Artificial Life");
    if (mainWindow == nullptr) {
        cerr << "Problem with creating a window";
        return 0;
    }
    
    bool quit = false;
    SDL_Event ev;

    SubjectsFactory &factory = SubjectsFactory::getInstance();

    SubjectsCollection &collection = SubjectsCollection::getInstance();
    Subject *pom = nullptr;
    for (int i = 1; i <= NUMBER_OF_TYPICAL_PLANTS; ++i)
    {
        pom = factory.create (2, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        collection.push(dynamic_cast<Plant*>(pom));
    }
    for (int i = 1; i <= NUMBER_OF_HERBIVORES; ++i)
    {
        pom = factory.create (1, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        collection.push(dynamic_cast<Herbivore*>(pom));
    }
    for (int i = 1; i<=NUMBER_OF_PREDATORS; ++i)
    {
        pom = factory.create(0, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        collection.push(dynamic_cast<Predator*>(pom));
    }

    vector<Subject*>::iterator ite;
    int cycleNumber = 0;
    bool reproductionPeriod = false;
    while(!quit)
    {
        while (SDL_PollEvent(&ev) != 0)
		{
		    //User requests quit
			if (ev.type == SDL_QUIT)
			{
				quit = true;
			}
		}
        collection.subjectsRound(cycleNumber, reproductionPeriod);

        mainWindow->clearScreen();
        mainWindow->createWeb (AREA_SIZE);

        collection.actualizeSubjectsPositionOnScreen(mainWindow);

        mainWindow->update();
        SDL_Delay(DELAY_TIME);
        if (cycleNumber == 99) {cycleNumber = 0;}
        else {cycleNumber++;}
        if (reproductionPeriod == false)
        {
            if(cycleNumber%REPRODUCTION_FREQUENCY == 0)
            {
                reproductionPeriod = true;
            }
        }
        else {
            if((cycleNumber-REPRODUCTION_FREQUENCY)%REPRODUCTION_PERIOD_LENGTH == 0)
            {
                reproductionPeriod = false;
            }
        }
    }

    mainWindow->deleteMainWindow();
    mainWindow = nullptr;

    /*for (ite = plantsCollection.begin(); ite != plantsCollection.end(); ++ite)
        delete *ite; 
        
    for (ite = herbivoresCollection.begin(); ite != herbivoresCollection.end(); ++ite)
        delete *ite;
    */
    collection.deleteAllSubjects();

    return 0;
}