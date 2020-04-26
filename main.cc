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

int main()
{
    MainWindow *mainwindow;
    try{
        mainwindow = mainwindow->getInstance(WINDOWWIDTH, WINDOWHEIGHT, "Artificial Life");
    }catch(std::exception &e){
        printf("Problem with creating a window");
        return 0;
    }
    
    bool quit = false;
    SDL_Event ev;

    SubjectsFactory factory;
    //kod testowy do usunięcia:
    vector<Subject*> subCollection;
    Subject *pom = nullptr;
    for(int i=1; i<NUMBEROFPLANTS; ++i)
    {
        pom = factory.create(2, WINDOWWIDTH/AREASIZE, WINDOWHEIGHT/AREASIZE, AREASIZE);
        subCollection.push_back(pom);
    }
    //dotąd usunąć - razem z deklaracją tablicy na górze

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
        for (ite = subCollection.begin(); ite != subCollection.end(); ++ite){
            mainwindow->drawPlant((*ite)->getXPosition(), (*ite)->getYPosition(), AREASIZE);
        }
        mainwindow->update();
        SDL_Delay(100);
    }
    return 0;
}