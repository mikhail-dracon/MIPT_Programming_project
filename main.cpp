#include <SFML/Graphics.hpp>
#include <iostream>
// #include <optional>
// #include <random>
#include "Available_Buildings.h"
#include "Map.h"
#include "Texture_List.h"
#include "Building_List.h"

// Размеры экрана
unsigned int SCREEN_WIDTH = 0;
unsigned int SCREEN_HEIGHT = 0;
// Параметры клеточки
float CELL_WIDTH = 0;
float CELL_HEIGHT= 0;
// Координаты нуля
float ZERO_X = 0;
float ZERO_Y = 0;
// Масштаб
float SCALE = 1;
float SCAIL_SPEED = 0.015; // Скорость зума
float SPEED = 40; // Скорость перемещения по карте
int FRAME_RATE = 60;

std::string BUILDING_TEXTURE = ""; // Текстура создаваемой сущности
int PLAYER_NUMBER = 1;
int MONEY = 1000;

Map Map_Build(unsigned int Map_Size, std::string Map_Texture) {
    Map Created_Map(Map_Size, Map_Texture);
    return Created_Map;
}

void Set_Sprite_Static_Position(sf::Sprite* Sprite, int x, int y) {
    float vector_x[2] = {0.5,-0.866};
    float vector_y[2] = {0.5,0.866};
    float k = 1/2.0f/0.88; // рассчет расстояния между клетками. Угол наклона = 30 градусов. На ширину спрайта домножаем ниже
    (*Sprite).setPosition({ZERO_Y+CELL_WIDTH*(x*vector_x[1]*k + y*vector_y[1]*k)*SCALE, ZERO_X+CELL_HEIGHT*(x*vector_x[0]*k + y*vector_y[0]*k)*SCALE});
}

void Map_Scale(int delta, std::string Scale_Type) {
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

void Pressed_Check(Map* Created_Map, Available_Buildings* available_buildings, Building_List* building_list, int x, int y) {
    for (int i = 0; i <Created_Map->Get_Size(); i++) {
        for (int j = 0; j <Created_Map->Get_Size(); j++) {
            float vector_x[2] = {0.5,-0.866};
            float vector_y[2] = {0.5,0.866};
            float k = 1/2.0f/0.88;
            int cell_x = ZERO_Y+CELL_WIDTH*(i*vector_x[1]*k + j*vector_y[1]*k)*SCALE;
            int cell_y = ZERO_X+CELL_HEIGHT*(i*vector_x[0]*k + j*vector_y[0]*k)*SCALE;
            if ((abs(cell_x - x) < CELL_WIDTH/2*SCALE*0.7) && (cell_y - y < CELL_HEIGHT*SCALE) && (cell_y - y > CELL_HEIGHT*SCALE*0.5)) {
                Set_Sprite_Static_Position(building_list->Find_Building("../Textures/FramePattern.png")->get_Sprite_Pointer(), i, j);
                building_list->Find_Building("../Textures/FramePattern.png")->set_x_coordinate(i);
                building_list->Find_Building("../Textures/FramePattern.png")->set_y_coordinate(j);
                if (BUILDING_TEXTURE != ""){ // Доступ к сущности уже был проверен перед вызовом
                    if ((*building_list).Add_Building(i,j,BUILDING_TEXTURE,BUILDING_TEXTURE)) {
                        MONEY -= 100;
                    } // Доделать определение ключа текстуры
                    building_list->Find_Building(i,j,BUILDING_TEXTURE)->set_Sprite_Origin(CELL_WIDTH/2.0f, CELL_HEIGHT*1.0f);
                    BUILDING_TEXTURE = "";
                }
            }
        }
    }
}

int main() {
    // Запуск окна
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    SCREEN_WIDTH = desktop.size.x;
    SCREEN_HEIGHT = desktop.size.y;
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Game");

    // Создаем эталонный спрайт мир для установки глобальных констант
    sf::Texture cell_texture;
    if (!cell_texture.loadFromFile("../Textures/BasicLendPattern.png")) {
        std::cerr << "Failed to load cell texture!" << std::endl;
        return 1;
    }
    sf::Sprite Sprite(cell_texture);
    sf::FloatRect scaledBounds = (Sprite).getGlobalBounds();
    CELL_WIDTH = scaledBounds.size.x; // Эталонный размер клетки
    CELL_HEIGHT = scaledBounds.size.y; // Эталонный размер клетки

    // Создание фона
    sf::Texture sky_texture;
    if (!sky_texture.loadFromFile("../Textures/Sky.png")) {
        std::cerr << "Failed to load sky texture!" << std::endl;
        return 1;
    }
    sf::Sprite Sky_Sprite(sky_texture);
    sf::FloatRect ScaledBounds = (Sky_Sprite).getGlobalBounds();
    float Sky_WIDTH = ScaledBounds.size.x;
    Sky_Sprite.setScale({SCREEN_WIDTH/Sky_WIDTH,SCREEN_WIDTH/Sky_WIDTH});

    // Установка начала координат
    ZERO_X = (SCREEN_HEIGHT/20)*8.0f;
    ZERO_Y = (SCREEN_WIDTH/2)*1.0f;

    // Создание карты
    std::string texture_name = "../Textures/BasicLendPattern.png";
    Map Created_Map = Map_Build(20, texture_name);

    // Создаем вектор из всех используемых текстур клеточек
    Texture_List texture_list(&Created_Map, "Standart");

    // Создаем словарь доступных для разных игроков сущностей
    Available_Buildings available_buildings;

    // Создаем вектор сущностей и добавляем в него рамку
    Building_List building_list;
    building_list.Add_Building(0,0,"../Textures/FramePattern.png","../Textures/FramePattern.png");
    building_list.Find_Building("../Textures/FramePattern.png")->set_Sprite_Origin(CELL_WIDTH/2.0f, CELL_HEIGHT*1.0f);
    building_list.Find_Building("../Textures/FramePattern.png")->set_Sprite_Color(255, 255, 255, 150);

    // Приступаем к переопределению клеточек
    for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
        for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
            texture_name = texture_list.creat_Random_Texture_Name(i, j);
            Created_Map.Cells_Data[i][j]->set_Sprite_By_Texture(texture_name);
            scaledBounds = (*(*Created_Map.Cells_Data[i][j]).get_Sprite_Pointer()).getGlobalBounds();
            // Установка корневой точки
            float width= scaledBounds.size.x;
            float height = scaledBounds.size.y;
            Created_Map.Cells_Data[i][j]->set_Sprite_Origin(width/2.0f, height*1.0f);
            // Установка позиции спрайта
            Set_Sprite_Static_Position(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer(),i,j);
        }
    }

    while (window.isOpen())
    {
        // Обработка ввода
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                Map_Scale(mouseWheelScrolled->delta, "Mouse");
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    Pressed_Check(&Created_Map, &available_buildings, &building_list ,mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                }
            }
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && (ZERO_X-(SCREEN_HEIGHT/2.0f)<SCREEN_HEIGHT/2.0f)){
            ZERO_X += SCALE*SPEED;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && (ZERO_X>SCALE*CELL_HEIGHT*0.577*(-1.0f)*Created_Map.Get_Size())){
            ZERO_X -= SCALE*SPEED;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && (ZERO_Y+SCALE*CELL_WIDTH*Created_Map.Get_Size()/2>0)){
            ZERO_Y -= SCALE*SPEED;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && (ZERO_Y-SCALE*CELL_WIDTH*Created_Map.Get_Size()/2<SCREEN_WIDTH)){
            ZERO_Y += SCALE*SPEED;
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) && (SCALE<1)) {
            Map_Scale(1, "Keyboard");
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) && (SCALE>0.2)) {
            Map_Scale(-1, "Keyboard");
        }

        // Обработка выбора сущности
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            available_buildings.Check_Access(1, "../Textures/grass.png");
            BUILDING_TEXTURE = "../Textures/grass.png";
        }

        // Отрисовка
        window.clear(sf::Color::Black);
        // Отрисовка фона
        window.draw(Sky_Sprite);
        // Отрисовка клеточек
        for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
            for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
                Set_Sprite_Static_Position(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer(), i, j);
                Created_Map.Cells_Data[i][j]->set_Scale_Sprite(SCALE);
                window.draw(*(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer()));
            }
        }
        // Отрисовка элементов из Building_List
        for (auto it = building_list.Buildings.begin(); it!= building_list.Buildings.end(); it++) {
            it->second->set_Sprite_Scale(SCALE);
            Set_Sprite_Static_Position(it->second->get_Sprite_Pointer(), it->second->get_x_coordinate(), it->second->get_y_coordinate());
            window.draw(*(it->second->get_Sprite_Pointer()));
        }

        window.display();
        sf::sleep(sf::milliseconds(1000/FRAME_RATE));

        // std::cout<<MONEY<<'\n';
    }
    std::cout << "Yep!" << std::endl;
}