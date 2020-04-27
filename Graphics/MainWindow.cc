//Andrzej Przybylski & Monika Berlinska
//Main window to visualize behaviour of creatures
#include "MainWindow.h"

MainWindow* MainWindow::pInstance_ = nullptr;

MainWindow::MainWindow(int w, int h, int area, std::string title)
{
    std::exception err;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        throw err;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		screenwidth = w;
		screenheight = h;
		//Create window
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenwidth, screenheight, SDL_WINDOW_SHOWN );
		if( window == nullptr )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            throw err;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			}
			else 
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
			//Get window surface
			//screensurface = SDL_GetWindowSurface( window );
		}
	}
	areasize = area;
}

void MainWindow::clearScreen()
{
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );	
}

void MainWindow::createWeb(int areasize)
{
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x99, 0xCC, 0xFF );	
	for (int i=0; i<screenheight; i+=areasize)
		SDL_RenderDrawLine( renderer, 0, i, screenwidth, i );
	for (int i=0; i<screenwidth; i+=areasize)
		SDL_RenderDrawLine( renderer, i, 0, i, screenheight );
}

void MainWindow::drawPlant(int x, int y)
{
	SDL_Rect plantRect = {x+1, y+1, areasize-1, areasize-1};
	SDL_SetRenderDrawColor( renderer, 0x00, 0x80, 0x00, 0xFF );		
	SDL_RenderFillRect( renderer, &plantRect );
}

void MainWindow::drawHerbivore(int x, int y)
{
	SDL_Rect plantRect = {x+1, y+1, areasize-1, areasize-1};
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );		
	SDL_RenderFillRect( renderer, &plantRect );
}

void MainWindow::drawPredator(int x, int y)
{
	SDL_Rect fillRect = { x, y, 100, 100 };
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( renderer, &fillRect );
}

void MainWindow::update()
{
	SDL_RenderPresent( renderer );
}

MainWindow::~MainWindow()
{
	//Deallocate surface
	SDL_FreeSurface( screensurface );
	screensurface = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

MainWindow* MainWindow::getInstance(int w, int h, int area, std::string title)
{
	if(!pInstance_)
		pInstance_ = new MainWindow(w, h, area, title);
	return pInstance_;
}