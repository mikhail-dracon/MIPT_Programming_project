#include "Building_List.h"
#include "barrak.h"
#include "unit.h"
#include "Miner.h"

std::string extract_filename(const std::string& path) {
    size_t start = path.find_last_of("/\\") + 1;
    size_t end = path.find_last_of('.');
    if (end == std::string::npos) end = path.length();
    // std::cout<<path.substr(start, end - start)<<'\n';
    return path.substr(start, end - start);
}

// Создаем дефолтный пустой словарь
Building_List::Building_List() {}

Building_List::~Building_List() {
    for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
        delete it->second;
    }
    Buildings.clear();
}

int Building_List::Count_Buildings(std::string key) {
    int number = 0;
    auto range = Buildings.equal_range(key);
    for (auto it = range.first; it != range.second; it++) {
        number++;
    }
    return number;
}

bool Building_List::Select_Building(int x, int y, std::string texture) {
    // for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
    //     if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y && it->first == "Barracks") {
    //         it->second->Action(-1);
    //     }
    // } // сбрасываем активность всех казарм

    if (texture == "../Textures/Miner.png" && Count_Buildings("Miner")<1 ) {
        for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
            if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y) {
                if (it->second->get_Teg() == "Mine") {
                    // it->second->Action(1);
                    std::string key = extract_filename(texture);
                    building* Building = new Miner(x, y, texture);
                    Buildings.insert(std::pair<std::string, building*>(key, Building));
                    return true;
                }
            }
        }
        return false;
    }

    if (texture == "../Textures/Barracks.png") {
        for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
            if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y) {
                if (it->second->get_Teg() == "Miner") {
                    // it->second->Action(1);
                    std::string key = extract_filename(texture);
                    building* Building = new Miner(x, y, texture);
                    Buildings.insert(std::pair<std::string, building*>(key, Building));
                    return true;
                }
            }
        }
        return false;
    }

    for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
        if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y) {
            if (it->second->get_Teg() == "Barracks") {
                // it->second->Action(1);
                std::string key = extract_filename(texture);
                building* Building = new unit(x, y, texture);
                Buildings.insert(std::pair<std::string, building*>(key, Building));
                return true;
            }
        }
    }
    return false;
}

// Добавляем новую постройку по известным координатам и текстуре (ВАЖНО! текстура - путь к соответствующему файлу в папку Textures)
bool Building_List::Add_Building(int x, int y, std::string texture) {
    std::string key = extract_filename(texture);
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
    if (texture == "../Textures/Barracks.png") {
        auto range = Buildings.equal_range("Mine");
        for (auto it = range.first; it != range.second; it++) {
            if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y) {
                return false;
            }
        }
    }
    // В случае, когда все хорошо, нам разрешают поставить здание
    if (key == "Mine") {
        building* Building = new building(x, y, texture);
        Buildings.insert(std::pair<std::string, building*>(key, Building));
        return true;
    } else if (key == "FramePattern") {
        building* Building = new building(x, y, texture);
        Buildings.insert(std::pair<std::string, building*>(key, Building));
        std::cout<<"Frame coordinate: "<<x<<" "<<y<<'\n';
        return true;
    } else {
        return Select_Building(x, y, texture);
    }
    /*else if (key == "grass" || key == "Warrior") {
        building* Building = new unit(x, y, texture);
        Buildings.insert(std::pair<std::string, building*>(key, Building));
    } else {
        building* Building = new building(x, y, texture);
        Buildings.insert(std::pair<std::string, building*>(key, Building));
    }*/
    return false;
}

// Чтобы уничтожить здание, нам нужно указать его координаты и владельца
// Метод Add_Building гарантированно не позволил создать дубликат, поэтому пушка-бомба, все должно работать
bool Building_List::Destroy_Building(int x_coord, int y_coord, std::string key) {
    auto range = Buildings.equal_range(key);
    for (auto it = range.first; it != range.second; it++) {
        if (it->second->get_x_coordinate() == x_coord && it->second->get_y_coordinate() == y_coord) {
            delete it->second;
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
    // std::cout<<"Try to Find: "<<key<<'\n';
    auto range = Buildings.equal_range(key);
    for (auto it = range.first; it != range.second; it++) {
        if (it->second->get_x_coordinate() == x_coord && it->second->get_y_coordinate() == y_coord) {
            // std::cout<<"Success Find: "<<key<<'\n';
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

void Building_List::Check_Health(int x_coord, int y_coord, std::string key) {
    if (Find_Building(x_coord, y_coord, key)->get_health() <= 0){
        Destroy_Building(x_coord, y_coord, key);
    }
}

void Building_List::Hit(int x, int y) {
    for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
        if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y) {
            if (it->second->get_Teg() == "Warrior" || it->second->get_Teg() == "Miner") {
                it->second->set_health(-50);
                Check_Health(x,y,it->first);
                return;
            } else if (it->second->get_Teg() == "Barracks") {
                it->second->set_health(-50);
                Check_Health(x,y,it->first);
                return;
            }
        }
    }
}

// bool Building_List::Move(int x, int y) {
//     for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
//         if (it->second->get_x_coordinate() == x && it->second->get_y_coordinate() == y) {
//             if (it->second->get_Teg() == "Warrior" || it->second->get_Teg() == "grass") {
//                 for (auto it1 = Buildings.begin(); it1 != Buildings.end(); it1++) {
//                     it1->second->Action(-1);
//                 } // сбрасываем активность всех воинов
//                 it->second->Action(1);
//                 return false;
//             }
//         }
//     }
//     // В случае если мы тыкнули не на солдата
//     for (auto it = Buildings.begin(); it != Buildings.end(); it++) {
//         if ((it->first == "Warrior" || it->first == "grass") && it->second->get_Action()) {
//             it->second->Action(-1);
//             it->second->set_x_coordinate(x);
//             it->second->set_y_coordinate(y);
//             return true;
//         }
//     } // сбрасываем активность всех воинов
// }

bool Building_List::Move(int x, int y) {
    // 2. Проверяем клик по юниту
    for (auto& pair : Buildings) {
        if (pair.second &&
            pair.second->get_x_coordinate() == x &&
            pair.second->get_y_coordinate() == y &&
            (pair.second->get_Teg() == "Warrior" || pair.second->get_Teg() == "Miner")) {
            for (auto& pair : Buildings) {
                if ((pair.first == "Warrior" || pair.first == "Miner") && pair.second) {
                    pair.second->Action(-1);
                }
            }
            pair.second->Action(1);
            return false;
            }
    }
    // 3. Если есть активный юнит - перемещаем его
    for (auto& pair : Buildings) {
        if (pair.second && (pair.first == "Warrior" || pair.first == "Miner") && pair.second->get_Action()) {
            if (abs(x-pair.second->get_x_coordinate())<2 && abs(y-pair.second->get_y_coordinate())<2) {
                pair.second->set_x_coordinate(x);
                pair.second->set_y_coordinate(y);
                pair.second->Action(-1); // Деактивируем после перемещения
                for (auto& pair : Buildings) {
                    if ((pair.first == "Warrior" || pair.first == "Miner") && pair.second) {
                        pair.second->Action(-1);
                        // I just want this shit to work 2:08 08.05.2025
                    }
                }
                return true;
            }
        }
    }
    return false;
}
