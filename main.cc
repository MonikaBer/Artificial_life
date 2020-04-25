#include<iostream>
#include"Graphics/MainWindow.h"

using namespace std;

static const int LEVELSIZE = 1000;
static const int WINDOWWIDTH = 640;
static const int WINDOWHEIGHT = 480;

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
        mainwindow->createWeb();
        mainwindow->update();
        SDL_Delay(100);
    }
    return 0;
}