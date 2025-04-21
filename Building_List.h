#ifndef BUILDING_LIST_H
#define BUILDING_LIST_H
#include <string>
#include <vector>
#include <map>
#include "building.h"

class Building_List {
    // std::multimap<std::string, building*> Buildings;
public:
    std::multimap<std::string, building*> Buildings;
    Building_List();
    ~Building_List();
    bool Add_Building(int x, int y, std::string key, std::string texture);
    bool Destroy_Building(int x_coord, int y_coord, std::string key);
    building* Find_Building(int x_coord, int y_coord, std::string key);
    building* Find_Building(std::string key);
};



#endif //BUILDING_LIST_H
