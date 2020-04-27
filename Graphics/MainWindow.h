//Andrzej Przybylski & Monika Berlinska
//Main window to visualize behaviour of creatures
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string>
#include<stdio.h>
#include<exception>

class MainWindow {
    public:
        static MainWindow* getInstance(int w, int h, int area, std::string title);
    private:
        static MainWindow* pInstance_;
        SDL_Window* window = nullptr;
        SDL_Surface* screensurface = nullptr;
        SDL_Renderer* renderer = nullptr;
        int screenwidth;
        int screenheight;
        int areasize;
        std::string screentitle;
        MainWindow(int w, int h, int area, std::string title);
        MainWindow(const MainWindow&) = delete;
        MainWindow& operator=(const MainWindow&) = delete;
        ~MainWindow();
    public:
        void clearScreen();
        void createWeb(int areasize);
        void drawPlant(int x, int y);
        void drawHerbivore(int x, int y);
        void drawPredator(int x, int y);
        void update();
};

#endif