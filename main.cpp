#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <cmath>
#include "Map.h"

// Размеры экрана
unsigned int SCREEN_WIDTH = 0;
unsigned int SCREEN_HEIGHT = 0;
// Параметры клеточки
float CELL_WIDTH = 0;
float CELL_HEIGHT= 0;
// Координаты нуля
float ZERO_X = 0;
float ZERO_Y = 0;

Map Map_Build(unsigned int Map_Size, std::string Map_Texture) {
    Map Created_Map(Map_Size, Map_Texture);
    return Created_Map;
}

void Set_Sprite_Static_Position(sf::Sprite* Sprite, int x, int y) {
    float vector_x[2] = {0.5,-0.866};
    float vector_y[2] = {0.5,0.866};
    float k = 1/2.0f/0.88; // рассчет расстояния между клетками. Угол наклона = 30 градусов. На ширину спрайта домножаем ниже
    (*Sprite).setPosition({ZERO_Y+CELL_WIDTH*(x*vector_x[1]*k + y*vector_y[1]*k), ZERO_X+CELL_HEIGHT*(x*vector_x[0]*k + y*vector_y[0]*k)});
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
    Map Created_Map = Map_Build(4, texture_name);
    for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
        for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
            int Texture_Number = std::rand()%100;
            if (Texture_Number >80) {
                texture_name = "../Textures/MarsMountainLendPattern.png";
            }else if (Texture_Number <40) {
                texture_name = "../Textures/MarsHoulLendPattern.png";
            }else {
                texture_name = "../Textures/MarsLendPattern.png";
            }
            Created_Map.Cells_Data[i][j]->set_Sprite_By_Texture(texture_name);
            sf::FloatRect scaledBounds = (*(*Created_Map.Cells_Data[i][j]).get_Sprite_Pointer()).getGlobalBounds();
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
        window.clear(sf::Color::Black);

        // Отрисовка клеточек
        for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
            for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
                window.draw(*(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer()));
            }
        }
        window.display();
    }
    std::cout << "Yep!" << std::endl;
}