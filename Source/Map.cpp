#include "Map.h"

Map::Map(unsigned int Map_Size, std::string Map_Texture) {
    // Создаем словарь доступных для разных игроков сущностей
    Available_Buildings *Available_buildings = new Available_Buildings();
    // Создаем вектор сущностей и добавляем в него рамку
    Building_List *Building_list = new Building_List();

    Size = Map_Size;
    for (int i=0; i < Size; i++) {
        std::vector<Cell*> Vector;
        for (int j=0; j < Size; j++) {
            Cell* New_Cell = new Cell(i, j, Map_Texture);
            Vector.push_back(New_Cell);
        }
        Cells_Data.push_back(Vector);
    }
    SCALE = 1;
    ZERO_X = 0;
    ZERO_Y = 0;
    CELL_WIDTH = 0;
    CELL_HEIGHT = 0;
    building_list = Building_list;
    available_buildings = Available_buildings;
    BUILDING_TEXTURE = "";
}

Map::~Map() {
    for (unsigned int i=0; i < Size; i++) {
        for (unsigned int j=0; j < Size; j++) {
            delete Cells_Data[i][j];
        }
    }
    Cells_Data.clear();
    delete building_list;
    delete available_buildings;
}

unsigned int Map::Get_Size() const {
    return Size;
}

void Map::set_scale(float scale) {
    SCALE = scale;
}

void Map::set_zero_y(float y) {
    ZERO_Y = y;
}

void Map::set_zero_x(float x) {
    ZERO_X = x;
}

void Map::set_cell_width(float w) {
    CELL_WIDTH = w;
}

void Map::set_cell_height(float h) {
    CELL_HEIGHT = h;
}

float Map::get_scale() {
    return SCALE;
}

float Map::get_zero_x() {
    return ZERO_X;
}

float Map::get_zero_y() {
    return ZERO_Y;
}

float Map::get_cell_width() {
    return CELL_WIDTH;
}

float Map::get_cell_height() {
    return CELL_HEIGHT;
}

void Map::set_building_list(Building_List* Building_list) {
    building_list = Building_list;
}

void Map::set_available_buildings(Available_Buildings* Available_buildings) {
    available_buildings = Available_buildings;
}

Building_List* Map::get_Building_list() {
    return building_list;
}

Available_Buildings *Map::get_Available_buildings() {
    return available_buildings;
}

void Map::set_BUILDING_TEXTURE(std::string texture) {
    BUILDING_TEXTURE = texture;
}


void Map::Set_Sprite_Static_Position(sf::Sprite* Sprite, int x, int y) {
    float vector_x[2] = {0.5,-0.866};
    float vector_y[2] = {0.5,0.866};
    float k = 1/2.0f/0.88; // рассчет расстояния между клетками. Угол наклона = 30 градусов. На ширину спрайта домножаем ниже
    (*Sprite).setPosition({ZERO_Y+CELL_WIDTH*(x*vector_x[1]*k + y*vector_y[1]*k)*SCALE, ZERO_X+CELL_HEIGHT*(x*vector_x[0]*k + y*vector_y[0]*k)*SCALE});
}

void Map::Pressed_Check(std::vector<int>* v) {
    int x = (*v)[0];
    int y = (*v)[1];
    // Устанавливаем рамку над нажатой клеточкой
    Set_Sprite_Static_Position(building_list->Find_Building("../Textures/FramePattern.png")->get_Sprite_Pointer(), building_list->Find_Building("../Textures/FramePattern.png")->get_x_coordinate(), building_list->Find_Building("../Textures/FramePattern.png")->get_y_coordinate());
    building_list->Find_Building("../Textures/FramePattern.png")->set_x_coordinate(x);
    building_list->Find_Building("../Textures/FramePattern.png")->set_y_coordinate(y);
    // Обрабатываем строительство
    if (BUILDING_TEXTURE != ""){ // Доступ к сущности уже был проверен перед вызовом
        if ((*building_list).Add_Building(x,y,BUILDING_TEXTURE,BUILDING_TEXTURE)) {
            // MONEY -= 100;
        } // Доделать определение ключа текстуры
        building_list->Find_Building(x,y,BUILDING_TEXTURE)->set_Sprite_Origin(CELL_WIDTH/2.0f, CELL_HEIGHT*1.0f);
        BUILDING_TEXTURE = "";
    }
}

std::vector<int> Map::get_pressed_sell_position(int x, int y) {
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j <Size; j++) {
            float vector_x[2] = {0.5,-0.866};
            float vector_y[2] = {0.5,0.866};
            float k = 1/2.0f/0.88;
            int cell_x = ZERO_Y+CELL_WIDTH*(i*vector_x[1]*k + j*vector_y[1]*k)*SCALE;
            int cell_y = ZERO_X+CELL_HEIGHT*(i*vector_x[0]*k + j*vector_y[0]*k)*SCALE;
            if ((abs(cell_x - x) < CELL_WIDTH/2*SCALE*0.7) && (cell_y - y < CELL_HEIGHT*SCALE) && (cell_y - y > CELL_HEIGHT*SCALE*0.5)) {
                std::vector<int> Return;
                Return.push_back(i);
                Return.push_back(j);
                Pressed_Check(&Return);
                return Return;
            }
        }
    }
    std::vector<int> Return;
    Return.push_back(-1);
    Return.push_back(-1);
    return Return;
}

void Map::Map_Scale(int delta, std::string Scale_Type, std::map<std::string, float>* Constants) {
    float SCAIL_SPEED = (*Constants)["SCAIL_SPEED"];
    // std::cout << "SCAIL_SPEED: " << SCAIL_SPEED << std::endl;
    float SCREEN_HEIGHT = (*Constants)["SCREEN_HEIGHT"];
    // std::cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << std::endl;
    float SCREEN_WIDTH = (*Constants)["SCREEN_WIDTH"];
    // std::cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << std::endl;
    if (Scale_Type == "Mouse") {
        delta*=5;
    }
    if ((delta > 0) && (SCALE<1)) {
        SCALE += SCAIL_SPEED*abs(delta);
        ZERO_X -= (SCREEN_HEIGHT/2-ZERO_X)*SCAIL_SPEED/SCALE*abs(delta);
        ZERO_Y -= (SCREEN_WIDTH/2-ZERO_Y)*SCAIL_SPEED/SCALE*abs(delta);
    }
    if ((delta < 0) && (SCALE>0.2)){
        SCALE -= SCAIL_SPEED*abs(delta);
        ZERO_X += (SCREEN_HEIGHT/2-ZERO_X)*SCAIL_SPEED/SCALE*abs(delta);
        ZERO_Y += (SCREEN_WIDTH/2-ZERO_Y)*SCAIL_SPEED/SCALE*abs(delta);
    }
}



