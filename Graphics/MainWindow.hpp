//Andrzej Przybylski & Monika Berlinska
//Main window to visualize behaviour of creatures
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <exception>
#include <iostream>

class MainWindow {
    private:
        static MainWindow* pInstance_;
        SDL_Window* window = nullptr;
        SDL_Surface* screenSurface = nullptr;
        SDL_Renderer* renderer = nullptr;
        int screenWidth;
        int screenHeight;
        int areaSize;
        std::string screenTitle;
        MainWindow(int w, int h, int area, std::string title);
        MainWindow(const MainWindow&) = delete;
        MainWindow& operator=(const MainWindow&) = delete;
        ~MainWindow();
    
    public:
        static MainWindow* getInstance(int w, int h, int area, std::string title);
  
        void clearScreen();
        void createWeb(int areaSize);
        void drawTypicalPlant(int x, int y);
        void drawSuperPlant(int x, int y);
        void drawHerbivore(int x, int y);
        void drawPredator(int x, int y);
        void update();
};

#endif