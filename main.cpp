#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <cmath>
#include "Map.h"

unsigned int SCREEN_WIDTH = 0;
unsigned int SCREEN_HEIGHT = 0;
float CELL_WIDTH = 0;
float CELL_HEIGHT= 0;

Map Map_Build(unsigned int Map_Size, std::string Map_Texture) {
    Map Created_Map(Map_Size, Map_Texture);
    return Created_Map;
}

void Set_Sprite_Static_Position(sf::Sprite* Sprite, int x, int y) {
    // координаты нуля:
    float zero_x = (SCREEN_HEIGHT/20)*8.0f;
    float zero_y = (SCREEN_WIDTH/2)*1.0f;
    // sf::FloatRect scaledBounds = (*Sprite).getGlobalBounds();
    // float width = scaledBounds.size.x;
    // float height = scaledBounds.size.y;
    float width = CELL_WIDTH;
    float height = CELL_HEIGHT;
    float vector_x[2] = {0.5,-0.866};
    float vector_y[2] = {0.5,0.866};
    float k = 1/2.0f/0.88; // рассчет расстояния между клетками. Угол наклона = 30 градусов. На ширину спрайта домножаем ниже
    // float length = pow(height*height + width*width, 0.5);
    (*Sprite).setPosition({zero_y+width*(x*vector_x[1]*k + y*vector_y[1]*k), zero_x+height*(x*vector_x[0]*k + y*vector_y[0]*k)});
}

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    SCREEN_WIDTH = desktop.size.x;
    SCREEN_HEIGHT = desktop.size.y;
    std::cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << std::endl;
    std::cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << std::endl;

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Game");

    // Подготовка спрайтов
    // Создаем карту и спрайты клеточек
    sf::Texture cell_texture;
    if (!cell_texture.loadFromFile("../Textures/MarsLendPattern.png")) {
        std::cerr << "Failed to load cell texture!" << std::endl;
        return 1;
    }
    sf::Sprite Sprite(cell_texture);
    sf::FloatRect scaledBounds = (Sprite).getGlobalBounds();
    CELL_WIDTH = scaledBounds.size.x;
    CELL_HEIGHT = scaledBounds.size.y;
    Map Created_Map = Map_Build(4, "../Textures/MarsLendPattern.png");
    for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
        for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
            int Texture_Number = std::rand()%100;
            std::cout << Texture_Number << std::endl;
            if (Texture_Number >80) {
                if (!cell_texture.loadFromFile("../Textures/MarsMountainLendPattern.png")) {
                    std::cerr << "Failed to load cell texture!" << std::endl;
                    return 1;
                } else {
                    ;
                }
            }else if (Texture_Number <40) {
                if (!cell_texture.loadFromFile("../Textures/MarsHoulLendPattern.png")) {
                    std::cerr << "Failed to load cell texture!" << std::endl;
                    return 1;
                }
            }else {
                if (!cell_texture.loadFromFile("../Textures/MarsLendPattern.png")) {
                    std::cerr << "Failed to load cell texture!" << std::endl;
                    return 1;
                }
            }
            Created_Map.Cells_Data[i][j]->set_Sprite(&cell_texture);
            sf::FloatRect scaledBounds = (*(*Created_Map.Cells_Data[i][j]).get_Sprite()).getGlobalBounds();
            float width= scaledBounds.size.x;
            float height = scaledBounds.size.y;
            Created_Map.Cells_Data[i][j]->set_Sprite_Origin(width/2.0f, height*1.0f);
            int x = Created_Map.Cells_Data[i][j]->get_x_coordinate();
            int y = Created_Map.Cells_Data[i][j]->get_y_coordinate();
            Set_Sprite_Static_Position(Created_Map.Cells_Data[i][j]->get_Sprite(),x,y);
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

        // Draw
        for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
            for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
                window.draw(*(Created_Map.Cells_Data[i][j]->get_Sprite()));
            }
        }
        // std::cout << "dwepne";
        // end the current frame
        window.display();
    }
}