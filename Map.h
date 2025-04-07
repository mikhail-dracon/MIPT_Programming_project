#ifndef MAP_H
#define MAP_H
#include <vector>
#include "Cell.h"

class Map{
    unsigned int Size;
    public:
    std::vector<std::vector<Cell*>> Cells_Data;
    Map(unsigned int Map_Size, std::string Map_Texture);
    ~Map();
    unsigned int Get_Size() const;
};

#endif //MAP_H
