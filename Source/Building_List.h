#ifndef BUILDING_LIST_H
#define BUILDING_LIST_H
#include <string>
#include <vector>
#include <map>
#include "building.h"
#include <iostream>

// Словарь, содержащий сведения о всех постройках на карте.
// (Он знает координаты, текстуры и владельцев каждого объекта)
// Ключ элемента = номеру игрока
// Текстура хранится в качестве строки указывающий на место хранения текстуры (папка Textures)

class Building_List {
    // std::multimap<std::string, building*> Buildings;
public:
    std::multimap<std::string, building*> Buildings;
    Building_List();
    ~Building_List();
    // Мы умеем добавлять новую постройку на карту
    bool Add_Building(int x, int y, std::string texture);
    // Мы умеем их удалять
    bool Destroy_Building(int x_coord, int y_coord, std::string key);
    // Если требуется обратиться к конкретному building снаружи, мы можем предоставить указатель на него
    building* Find_Building(int x_coord, int y_coord, std::string key);
    building* Find_Building(std::string key);
    void Check_Health(int x_coord, int y_coord, std::string key);
    void Hit(int x_coord, int y_coord);
    bool Move(int x_coord, int y_coord);
    bool Select_Building(int x_coord, int y_coord, std::string texture);
    int Count_Buildings(std::string key);
    int Stonks(int PLAYER_NUMBER);
};



#endif //BUILDING_LIST_H