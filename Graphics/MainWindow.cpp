//Andrzej Przybylski & Monika Berlinska
//Main window to visualize behaviour of creatures
#include "MainWindow.hpp"

using namespace std;

MainWindow* MainWindow::pInstance_ = nullptr;

MainWindow::MainWindow (int w, int h, int area, string title) 
{
	areaSize = area;

    exception err;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cerr << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        throw err;
		return;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) 
	{
		cerr << "Warning: Linear texture filtering not enabled!";
		return;
	}

	screenWidth = w;
	screenHeight = h;
	
	//Create window
	window = SDL_CreateWindow (title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		cerr << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
		throw err;
		return;
	}
	
	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cerr << "Renderer could not be created! SDL Error: %s\n", SDL_GetError();
		return;
	}
	//Initialize renderer color
	SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Get window surface
	//screenSurface = SDL_GetWindowSurface( window );
}


void MainWindow::clearScreen()
{
	SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear (renderer);	
}

void MainWindow::createWeb (int areaSize)
{
	SDL_SetRenderDrawColor (renderer, 0xFF, 0x99, 0xCC, 0xFF);	
	for (int i = 0; i < screenHeight; i += areaSize)
		SDL_RenderDrawLine (renderer, 0, i, screenWidth, i);
	for (int i = 0; i < screenWidth; i += areaSize)
		SDL_RenderDrawLine (renderer, i, 0, i, screenHeight);
}

void MainWindow::drawTypicalPlant (int x, int y)
{
	SDL_Rect plantRect = {x+1, y+1, areaSize-1, areaSize-1};
	SDL_SetRenderDrawColor (renderer, 0x00, 0x80, 0x00, 0xFF);		
	SDL_RenderFillRect (renderer, &plantRect);
}

void MainWindow::drawSuperPlant (int x, int y)
{
	SDL_Rect plantRect = {x+1, y+1, areaSize-1, areaSize-1};
	SDL_SetRenderDrawColor (renderer, 0x00, 0x80, 0x00, 0xFF);		
	SDL_RenderFillRect (renderer, &plantRect);
}

void MainWindow::drawHerbivore (int x, int y)
{
	SDL_Rect plantRect = {x+1, y+1, areaSize-1, areaSize-1};
	SDL_SetRenderDrawColor (renderer, 0x00, 0x00, 0xFF, 0xFF);		
	SDL_RenderFillRect (renderer, &plantRect);
}

void MainWindow::drawPredator (int x, int y)
{
	SDL_Rect fillRect = {x, y, 100, 100};
	SDL_SetRenderDrawColor (renderer, 0xFF, 0x00, 0x00, 0xFF);		
	SDL_RenderFillRect (renderer, &fillRect);
}

void MainWindow::update()
{
	SDL_RenderPresent (renderer);
}

MainWindow::~MainWindow()
{
	//Deallocate surface
	SDL_FreeSurface (screenSurface);
	screenSurface = NULL;

	//Destroy window
	SDL_DestroyWindow (window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

MainWindow* MainWindow::getInstance (int w, int h, int area, string title)
{
	if (!pInstance_)
		pInstance_ = new MainWindow (w, h, area, title);
	return pInstance_;
}