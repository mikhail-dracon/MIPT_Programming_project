#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <random>
#include "Map.h"
#include "Texture_List.h"

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
float SCAIL_SPEED = 0.015;
float SPEED = 40;
int FRAME_RATE = 60;

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

// Чем больше одинаковых элементов, тем больше шанс его спавна
void fill_texture_vector(std::vector<std::string>* Texture_Vector) {
    Texture_Vector->push_back("../Textures/MarsLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsMountainLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsMountainLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsHoulLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsHoulLendPattern.png");
    Texture_Vector->push_back("../Textures/MarsHoulLendPattern.png");
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

    // Установка начала координат
    ZERO_X = (SCREEN_HEIGHT/20)*8.0f;
    ZERO_Y = (SCREEN_WIDTH/2)*1.0f;

    // Создание карты
    std::string texture_name = "../Textures/BasicLendPattern.png";
    Map Created_Map = Map_Build(20, texture_name);
    // Создаем вектор из всех используемых текстур клеточек
    std::vector<std::string> Texture_Vector;
    fill_texture_vector(&Texture_Vector);
    Texture_List texture_list(&Created_Map, Texture_Vector);
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
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
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
            SCALE += SCAIL_SPEED;
            ZERO_X -= (SCREEN_HEIGHT/2-ZERO_X)*SCAIL_SPEED/SCALE;
            ZERO_Y -= (SCREEN_WIDTH/2-ZERO_Y)*SCAIL_SPEED/SCALE;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) && (SCALE>0.2)){
            SCALE -= SCAIL_SPEED;
            ZERO_X += (SCREEN_HEIGHT/2-ZERO_X)*SCAIL_SPEED/SCALE;
            ZERO_Y += (SCREEN_WIDTH/2-ZERO_Y)*SCAIL_SPEED/SCALE;
        }

        window.clear(sf::Color::Black);
        // Отрисовка клеточек
        for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
            for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
                Set_Sprite_Static_Position(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer(), i, j);
                Created_Map.Cells_Data[i][j]->set_Scale_Sprite(SCALE);
                window.draw(*(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer()));
            }
        }
        window.display();
        sf::sleep(sf::milliseconds(1000/FRAME_RATE));
    }
    std::cout << "Yep!" << std::endl;
}