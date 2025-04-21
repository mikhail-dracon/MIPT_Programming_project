#ifndef AVAILABLE_BUILDINGS_H
#define AVAILABLE_BUILDINGS_H

#include <string>
#include <map>

class Available_Buildings {
public:
    std::multimap<int, std::string> Buildings;
    Available_Buildings();
    ~Available_Buildings();
    bool Check_Access(int Player_Number, std::string);
};



#endif //AVAILABLE_BUILDINGS_H
