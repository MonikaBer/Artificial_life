#include<iostream>
#include<vector>
#include"Graphics/MainWindow.h"
#include"Subjects/SubjectsFactory.hpp"

using namespace std;

static const int AREASIZE = 5;
static const int WINDOWWIDTH = 640;
static const int WINDOWHEIGHT = 480;

//starting number of subjects:
static const int NUMBEROFPLANTS = 40;
static const int NUMBEROFHERBIVORE = 10;

int main()
{
    MainWindow *mainwindow;
    try{
        mainwindow = mainwindow->getInstance(WINDOWWIDTH, WINDOWHEIGHT, AREASIZE, "Artificial Life");
    }catch(std::exception &e){
        printf("Problem with creating a window");
        return 0;
    }
    
    bool quit = false;
    SDL_Event ev;

    SubjectsFactory factory;

    vector<Subject*> plantCollection;
    Subject *pom = nullptr;
    for(int i=1; i<NUMBEROFPLANTS; ++i)
    {
        pom = factory.create(2, WINDOWWIDTH/AREASIZE, WINDOWHEIGHT/AREASIZE, AREASIZE);
        plantCollection.push_back(pom);
    }
    vector<Subject*> herbivoreCollection;
    for (int i=1; i<NUMBEROFHERBIVORE; ++i)
    {
        pom = factory.create(1, WINDOWWIDTH/AREASIZE, WINDOWHEIGHT/AREASIZE, AREASIZE);
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
        mainwindow->clearScreen();
        mainwindow->createWeb(AREASIZE);
        vector<Subject*>::iterator ite;
        for (ite = plantCollection.begin(); ite != plantCollection.end(); ++ite){
            mainwindow->drawPlant((*ite)->getXPosition(), (*ite)->getYPosition());
        }
        for (ite = herbivoreCollection.begin(); ite != herbivoreCollection.end(); ++ite){
            mainwindow->drawHerbivore((*ite)->getXPosition(), (*ite)->getYPosition());
        }
        mainwindow->update();
        SDL_Delay(100);
    }
    return 0;
}