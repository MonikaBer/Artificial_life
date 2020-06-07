//Andrzej Przybylski & Monika Berlinska
//Class responsible for reading data from config file
#ifndef SIMULATIONPARAMETERS_HPP
#define SIMULATIONPARAMETERS_HPP
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

    int AREA_SIZE = 10;
    int WINDOW_WIDTH = 640;
    int WINDOW_HEIGHT = 480;
    int ONE_CYCLE_SIZE = 100;
    int SIMULATION_SPEED = 10;
    int DELAY_TIME = 1000/SIMULATION_SPEED;
    int REPRODUCTION_FREQUENCY = 50;
    int REPRODUCTION_PERIOD_LENGTH = 10;
    int NUMBER_OF_TYPICAL_PLANTS = 40;
    int NUMBER_OF_HERBIVORES = 10;
    int NUMBER_OF_PREDATORS = 5;
    int MAX_LIFE_TIME = 250;
    int VIEW_SIZE = 100;

class SimulationParameters {
    private:
        ifstream configFile;
    public:
        SimulationParameters(string fileName)
        {   string variableName;
            string variableValue;
            configFile.open(fileName.c_str());
            if(configFile)
            {
                while(configFile >> variableName >> variableValue)
                {
                    if(variableName == "AREA_SIZE")
                        AREA_SIZE = stoi(variableValue);
                    else if(variableName == "WINDOW_WIDTH")
                        WINDOW_WIDTH = stoi(variableValue);
                    else if(variableName == "WINDOW_HEIGHT")
                        WINDOW_HEIGHT = stoi(variableValue);
                    else if(variableName == "ONE_CYCLE_SIZE")
                        ONE_CYCLE_SIZE = stoi(variableValue);
                    else if(variableName == "SIMULATION_SPEED"){
                        SIMULATION_SPEED = stoi(variableValue);
                        DELAY_TIME = 1000/SIMULATION_SPEED;}
                    else if(variableName == "REPRODUCTION_FREQUENCY")
                        REPRODUCTION_FREQUENCY = stoi(variableValue);
                    else if(variableName == "REPRODUCTION_PERIOD_LENGTH")
                        REPRODUCTION_PERIOD_LENGTH = stoi(variableValue);
                    else if(variableName == "NUMBER_OF_TYPICAL_PLANTS")
                        NUMBER_OF_TYPICAL_PLANTS = stoi(variableValue);
                    else if(variableName == "NUMBER_OF_HERBIVORES")
                        NUMBER_OF_HERBIVORES = stoi(variableValue);
                    else if(variableName == "NUMBER_OF_PREDATORS")
                        NUMBER_OF_PREDATORS = stoi(variableValue);
                    else if(variableName == "MAX_LIFE_TIME")
                        MAX_LIFE_TIME = stoi(variableValue);
                    else if(variableName == "VIEW_SIZE")
                        VIEW_SIZE = stoi(variableValue);
                }
            }
            else {
                cout << "Error with open configuration file" << endl;
            }
            configFile.close();
        }

        int getAreaSize(){return AREA_SIZE;}
        int getWindowWidth(){return WINDOW_WIDTH;}
        int getWindowHeight(){return WINDOW_HEIGHT;}
        int getOneCycleSize(){return ONE_CYCLE_SIZE;}
        int getSimulationSpeed(){return SIMULATION_SPEED;}
        int getDelayTime(){return DELAY_TIME;}
        int getReproductionFrequency(){return REPRODUCTION_FREQUENCY;}
        int getReproductionPeriodLength(){return REPRODUCTION_PERIOD_LENGTH;}
        int getNumberOfTypicalPlants(){return NUMBER_OF_TYPICAL_PLANTS;}
        int getNumberOfHerbivores(){return NUMBER_OF_HERBIVORES;}
        int getNumberOfPredators(){return NUMBER_OF_PREDATORS;}
        int getMaxLifeTime(){return MAX_LIFE_TIME;}
        int getViewSize(){return VIEW_SIZE;}
};  

#endif