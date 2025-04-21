#include "Available_Buildings.h"

// Каждый ключ соответствует своему игроку и дает ему доступ к сущности
Available_Buildings::Available_Buildings() {
    Buildings.insert(std::pair<int, std::string>(1, "../grass.png"));
}

Available_Buildings::~Available_Buildings() {
    Buildings.clear();
}

bool Available_Buildings::Check_Access(int Player_Number, std::string building_name) {
    auto range = Buildings.equal_range(Player_Number);
    for (auto it = range.first; it != range.second; it++) {
        if (it->second == building_name) {
            return true;
        }
    }
    return false;
}

