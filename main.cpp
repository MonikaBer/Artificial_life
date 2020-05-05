#include <iostream>
#include <vector>
#include "Graphics/MainWindow.hpp"
#include "Subjects/SubjectsFactory.hpp"

using namespace std;

static const int AREA_SIZE = 5;
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

static const int REPRODUCTION_FREQUENCY = 50;       //break between reproduction periods    

//starting number of subjects:
static const int NUMBER_OF_TYPICAL_PLANTS = 40;
static const int NUMBER_OF_HERBIVORES = 10;
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

    SubjectsFactory&factory = SubjectsFactory::getInstance();

    vector<Subject*> plantsCollection;
    Subject *pom = nullptr;
    for (int i = 1; i < NUMBER_OF_TYPICAL_PLANTS; ++i)
    {
        pom = factory.create (2, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        plantsCollection.push_back(pom);
    }
    vector<Subject*> herbivoresCollection;
    for (int i = 1; i < NUMBER_OF_HERBIVORES; ++i)
    {
        pom = factory.create (1, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        herbivoresCollection.push_back(pom);
    }

    vector<Subject*>::iterator ite;
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
        mainWindow->clearScreen();
        mainWindow->createWeb (AREA_SIZE);
        
        for (ite = plantsCollection.begin(); ite != plantsCollection.end(); ++ite) {
            mainWindow->drawTypicalPlant ((*ite)->getXPosition(), (*ite)->getYPosition());
        }
        for (ite = herbivoresCollection.begin(); ite != herbivoresCollection.end(); ++ite) { 
            mainWindow->drawHerbivore ((*ite)->getXPosition(), (*ite)->getYPosition());
        }
        mainWindow->update();
        SDL_Delay(100);
    }

    mainWindow->deleteMainWindow();
    mainWindow = nullptr;

    for (ite = plantsCollection.begin(); ite != plantsCollection.end(); ++ite)
        delete *ite; 
        
    for (ite = herbivoresCollection.begin(); ite != herbivoresCollection.end(); ++ite)
        delete *ite;
    

    return 0;
}