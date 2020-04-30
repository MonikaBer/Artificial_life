#include <iostream>
#include <vector>
#include "Graphics/MainWindow.h"
#include "Subjects/SubjectsFactory.hpp"

using namespace std;

static const int AREA_SIZE = 5;
static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;

//starting number of subjects:
static const int NUMBER_OF_PLANTS = 40;
static const int NUMBER_OF_HERBIVORES = 10;

int main()
{
    MainWindow *mainWindow;
    try {
        mainWindow = mainWindow->getInstance(WINDOW_WIDTH, WINDOW_HEIGHT, AREA_SIZE, "Artificial Life");
    } catch (std::exception &e) {
        printf("Problem with creating a window");
        return 0;
    }
    
    bool quit = false;
    SDL_Event ev;

    SubjectsFactory&factory = SubjectsFactory::getInstance();

    vector<Subject*> plantCollection;
    Subject *pom = nullptr;
    for (int i = 1; i < NUMBER_OF_PLANTS; ++i)
    {
        pom = factory.create(2, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE);
        plantCollection.push_back(pom);
    }
    vector<Subject*> herbivoreCollection;
    for (int i = 1; i < NUMBER_OF_HERBIVORES; ++i)
    {
        pom = factory.create(1, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE);
        herbivoreCollection.push_back(pom);
    }

    while(!quit)
    {
        while(SDL_PollEvent( &ev ) != 0 )
		{
		    //User requests quit
			if( ev.type == SDL_QUIT )
			{
				quit = true;
			}
		}
        mainWindow->clearScreen();
        mainWindow->createWeb(AREA_SIZE);
        vector<Subject*>::iterator ite;
        for (ite = plantCollection.begin(); ite != plantCollection.end(); ++ite) {
            mainWindow->drawPlant((*ite)->getXPosition(), (*ite)->getYPosition());
        }
        for (ite = herbivoreCollection.begin(); ite != herbivoreCollection.end(); ++ite) { 
            mainWindow->drawHerbivore((*ite)->getXPosition(), (*ite)->getYPosition());
        }
        mainWindow->update();
        SDL_Delay(100);
    }
    return 0;
}