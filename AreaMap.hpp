//Andrzej Przybylski & Monika Berlinska
//base class for area of subjects' living
#ifndef AREA_MAP_HPP
#define AREA_MAP_HPP
#include <map>
#include <vector>
#include "Subjects/Subject.hpp"
#include "helper.hpp"

class AreaMap {
    private:
        std::map<Coordinates, Subject*> subjectsPositions;
        int width;
        int height;

    public:
        AreaMap(){}
        AreaMap(const AreaMap&) = delete;
        AreaMap& operator=(const AreaMap&) = delete;

        static AreaMap& getInstance(){
            static AreaMap instance;
            return instance;
        }

        std::vector<Coordinates> returnFreeAdjacentPositions(Coordinates position);
        bool isProhibitedPosition(Coordinates checkedPosition);

        void insert(Coordinates position, Subject* sub);
        std::map<Coordinates, Subject*>::iterator find(Coordinates position);
        int count(Coordinates position);        
        std::map<Coordinates, Subject*>::iterator begin();
        std::map<Coordinates, Subject*>::iterator end();
        void erase(std::map<Coordinates, Subject*>::iterator it);
        void clear();

        //getters
        std::map<Coordinates, Subject*> getSubjectsPositions() const;
        int getWidth() const;
        int getHeight() const;
        
        //setters
        void setSize(int newWidth, int newHeight);
};

#endif