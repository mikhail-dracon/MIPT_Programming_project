#include "Map.h"

Map::Map(unsigned int Map_Size, std::string Map_Texture) {
    Size = Map_Size;
    for (int i=0; i < Size; i++) {
        std::vector<Cell*> Vector;
        for (int j=0; j < Size; j++) {
            Cell* New_Cell = new Cell(i, j, Map_Texture);
            Vector.push_back(New_Cell);
        }
        Cells_Data.push_back(Vector);
    }
}

Map::~Map() {
    for (unsigned int i=0; i < Size; i++) {
        for (unsigned int j=0; j < Size; j++) {
            delete Cells_Data[i][j];
        }
    }
    Cells_Data.clear();
}

unsigned int Map::Get_Size() const {
    return Size;
}



