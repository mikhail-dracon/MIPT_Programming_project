#include "Building_List.h"

// Создаем дефолтный пустой словарь
Building_List::Building_List() {}

Building_List::~Building_List() {
    Buildings.clear();
}

// Добавляем новую постройку по известным координатам и текстуре (ВАЖНО! текстура - путь к соответствующему файлу в папку Textures)
bool Building_List::Add_Building(int x, int y, std::string key, std::string texture) {
    // Следующей строкой мы говорим программе, элементы с каким ключом принимать в внимание
    auto range = Buildings.equal_range(key);
    // Пока что в программе есть дыра и противники могут создавать здания вместе на одной клеточке

    // Цикл пробегается по всем уже существующим постройкам и смотрит, не хотим ли мы дублировать одну из них
    for (auto it = range.first; it != range.second; it++) {
        if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y) {
            // it->second->get_Texture_Name() == texture;
            // Тут он понял, что мы создаем дубликат и отказывает нам => объект не создается, игрок не тратит деньги
            return false;
        }
    }
    // В случае, когда все хорошо, нам разрешают поставить здание
    building* Building = new building(x, y, texture);
    Buildings.insert(std::pair<std::string, building*>(key, Building));
    return true;
}

// Чтобы уничтожить здание, нам нужно указать его координаты и владельца
// Метод Add_Building гарантированно не позволил создать дубликат, поэтому пушка-бомба, все должно работать
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

// Чтобы найти указатель на интересующий нас элемент, мы должны знать его координату и владельца
// (Метод Add опять постарался над однозначностью определения)
building* Building_List::Find_Building(int x_coord, int y_coord, std::string key) {
    // Будем пробегаться только по постройкам одного владельца
    auto range = Buildings.equal_range(key);
    for (auto it = range.first; it != range.second; it++) {
        if (it->second->get_x_coordinate() == x_coord && it->second->get_y_coordinate() == y_coord) {
            return it->second;
        }
    }
    // На нет и суда нет, ЙОУ!
    return nullptr;
}

// Метод поиска для избранных
// Таким объектом например является рамка Frame, она одна в своем роде и имеет собственное значение ключа
building* Building_List::Find_Building(std::string key) {
    if (Buildings.find(key) != Buildings.end()) {
        return(Buildings.find(key)->second);
    }
    return nullptr;
}

