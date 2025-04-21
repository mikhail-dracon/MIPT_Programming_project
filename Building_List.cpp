#include "Building_List.h"

Building_List::Building_List() {}

Building_List::~Building_List() {
    Buildings.clear();
}


bool Building_List::Add_Building(int x, int y, std::string key, std::string texture) {
    auto range = Buildings.equal_range(key);
    for (auto it = range.first; it != range.second; it++) {
        if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y) {
            it->second->get_Texture_Name() == texture;
            return false;
        }
    }
    building* Building = new building(x, y, texture);
    Buildings.insert(std::pair<std::string, building*>(key, Building));
    return true;
}

bool Building_List::Destroy_Building(int x_coord, int y_coord, std::string key) {
    auto range = Buildings.equal_range(key);
    for (auto it = range.first; it != range.second; it++) {
        if (it->second->get_x_coordinate() == x_coord && it->second->get_y_coordinate() == y_coord) {
            Buildings.erase(it);
            return true;
        }
    }
    return false;
}

building* Building_List::Find_Building(int x_coord, int y_coord, std::string key) {
    auto range = Buildings.equal_range(key);
    for (auto it = range.first; it != range.second; it++) {
        if (it->second->get_x_coordinate() == x_coord && it->second->get_y_coordinate() == y_coord) {
            return it->second;
        }
    }
    return nullptr;
}

building* Building_List::Find_Building(std::string key) {
    if (Buildings.find(key) != Buildings.end()) {
        return(Buildings.find(key)->second);
    }
    return nullptr;
}

