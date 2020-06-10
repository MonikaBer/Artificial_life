#include <iostream>
#include <vector>
#include "Subjects/SubjectsCollection.hpp"
#include "SimulationParameters.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        string fName(argv[1]);
        SimulationParameters par(fName);
    }
    
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
        pom = factory.create(TYPICAL_PLANT, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        while (!collection.push(dynamic_cast<Plant*>(pom)))
            pom = factory.create(TYPICAL_PLANT, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
    }
    for (int i = 0; i < NUMBER_OF_HERBIVORES; ++i)
    {
        pom = factory.create(HERBIVORE, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        while (!collection.push(dynamic_cast<Herbivore*>(pom)))
            pom = factory.create(HERBIVORE, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
    }
    for (int i = 0; i< NUMBER_OF_PREDATORS; ++i)
    {
        pom = factory.create(PREDATOR, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        while (!collection.push(dynamic_cast<Predator*>(pom)))
            pom = factory.create(PREDATOR, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
    }
    vector<Subject*>::iterator ite;
    int cycleNumber = 1;
    int mouseX, mouseY;
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
            else if(ev.type == SDL_KEYDOWN)
            {
                if(ev.key.keysym.sym == SDLK_p)
                    {simulationPaused = true;}
                if (ev.key.keysym.sym == SDLK_u)
                    {simulationPaused = false;}
            }
            if(simulationPaused){
                if(ev.type == SDL_MOUSEBUTTONDOWN && SDL_GetMouseState(&mouseX, &mouseY))
                {
                    collection.getSubjectInfoFromPosition(make_pair(mouseX/AREA_SIZE, mouseY/AREA_SIZE));
                }
            }
		}
        if (!simulationPaused){
            collection.subjectsRound(reproductionPeriod, MAX_LIFE_TIME, VIEW_SIZE);

            //increase number of plants to NUMBER_OF_TYPICAL_PLANTS
            for (int i = 0; i < NUMBER_OF_TYPICAL_PLANTS - collection.getPlantsNumber(); ++i)
            {
                pom = factory.create(TYPICAL_PLANT, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME);
                while (!collection.push(dynamic_cast<Plant*>(pom)))
                    pom = factory.create(TYPICAL_PLANT, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME);
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