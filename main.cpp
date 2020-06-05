#include <iostream>
#include <vector>
#include "Subjects/SubjectsCollection.hpp"
#include "helper.hpp"
#include "SimulationParameters.hpp"

using namespace std;

SimulationParameters par("../configure.txt");

int AREA_SIZE = par.getAreaSize();
int WINDOW_WIDTH = par.getWindowWidth();
int WINDOW_HEIGHT = par.getWindowHeight();

int ONE_CYCLE_SIZE = par.getOneCycleSize();
int SIMULATION_SPEED = par.getSimulationSpeed();             //number between 1 and 100
int DELAY_TIME = par.getDelayTime();

int REPRODUCTION_FREQUENCY = par.getReproductionFrequency();       //break between reproduction periods
int REPRODUCTION_PERIOD_LENGTH = par.getReproductionPeriodLength();    

//starting number of subjects:
int NUMBER_OF_TYPICAL_PLANTS = par.getNumberOfTypicalPlants();
int NUMBER_OF_HERBIVORES = par.getNumberOfHerbivores();
int NUMBER_OF_PREDATORS = par.getNumberOfPredators();
int MAX_LIFE_TIME = par.getMaxLifeTime();
int VIEW_SIZE = par.getViewSize();

int main()
{
    //SimulationParameters par("configure.txt");
    //AREA_SIZE = par.getAreaSize();
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
    collection.setSizeOfAreaMap(WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE);
    Subject *pom = nullptr;
    for (int i = 0; i < NUMBER_OF_TYPICAL_PLANTS; ++i)
    {
        pom = factory.create(2, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        while (!collection.push(dynamic_cast<Plant*>(pom)))
            pom = factory.create(2, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
    }
    for (int i = 0; i < NUMBER_OF_HERBIVORES; ++i)
    {
        pom = factory.create(1, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        while (!collection.push(dynamic_cast<Herbivore*>(pom)))
            pom = factory.create(1, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
    }
    for (int i = 0; i< NUMBER_OF_PREDATORS; ++i)
    {
        pom = factory.create(0, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        while (!collection.push(dynamic_cast<Predator*>(pom)))
            pom = factory.create(0, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
    }

    vector<Subject*>::iterator ite;
    int cycleNumber = 0;
    bool reproductionPeriod = false;
    bool simulationPaused = false;
    while(!quit)
    {
        while (SDL_PollEvent(&ev) != 0)
		{
		    //User requests quit
			if (ev.type == SDL_QUIT)
			{
				quit = true;
			}
            else if(ev.type = SDL_KEYDOWN)
            {
                if(ev.key.keysym.sym == SDLK_p)
                    {simulationPaused = true;}
                if (ev.key.keysym.sym == SDLK_u)
                    {simulationPaused = false;}
            }
		}
        if (!simulationPaused){
            collection.subjectsRound(reproductionPeriod, MAX_LIFE_TIME, VIEW_SIZE);

            //increase number of plants to NUMBER_OF_TYPICAL_PLANTS
            for (int i = 0; i < NUMBER_OF_TYPICAL_PLANTS - collection.getPlantsNumber(); ++i)
            {
                pom = factory.create(2, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
                while (!collection.push(dynamic_cast<Plant*>(pom)))
                    pom = factory.create(2, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
            }

            mainWindow->clearScreen();
            mainWindow->createWeb(AREA_SIZE);
            collection.actualizeSubjectsPositionOnScreen(mainWindow);
            mainWindow->update();
            SDL_Delay(DELAY_TIME);

            if (!reproductionPeriod)
            {
                if (cycleNumber % REPRODUCTION_FREQUENCY == 0)
                {
                    reproductionPeriod = true;
                }
            }
            else {
                if ((cycleNumber - REPRODUCTION_PERIOD_LENGTH) % REPRODUCTION_FREQUENCY == 0)
                {
                    reproductionPeriod = false;
                }
            }

            if (cycleNumber == ONE_CYCLE_SIZE-1)  cycleNumber = 0;
            else  cycleNumber++;
        }
    }

    mainWindow->deleteMainWindow();
    mainWindow = nullptr;
    collection.deleteAllSubjects();
    return 0;
}