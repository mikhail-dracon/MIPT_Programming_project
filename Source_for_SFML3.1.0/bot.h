//
// Created by User on 10.05.2025.
//

#ifndef SOURCE_BOT_H
#define SOURCE_BOT_H
#include "Map.h"

class bot {
private:
    int money;
    Map* map;
    Building_List* building_list;
    Available_Buildings* available_buildings;
public:
    bot(Map* MAP);
    ~bot();
    void SuperFunction();
};


#endif //SOURCE_BOT_H
