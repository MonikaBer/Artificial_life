//Andrzej Przybylski & Monika Berlinska
//Main window to visualize behaviour of creatures
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string>
#include<stdio.h>
#include<exception>

class MainWindow {
    public:
        static MainWindow* getInstance(int w, int h, std::string title);
    private:
        static MainWindow* pInstance_;
        SDL_Window* window = nullptr;
        SDL_Surface* screensurface = nullptr;
        SDL_Renderer* renderer = nullptr;
        int screenwidth;
        int screenheight;
        std::string screentitle;
        MainWindow(int w, int h, std::string title);
        ~MainWindow();
    public:
        void clearScreen();
        void createWeb();
        void drawPredator(int x, int y);
        void update();   
};