#ifndef CELL_H
#define CELL_H
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Cell {
    int x_coordinate;
    int y_coordinate;
    sf::Sprite* Sprite;
    sf::Texture Texture;
    std::string Texture_Name;
public:
    Cell(int x, int y, std::string texture);
    ~Cell();
    int get_x_coordinate() const;
    int get_y_coordinate() const;
    std::string get_Texture_Name() const;
    sf::Sprite* get_Sprite_Pointer() const;
    void set_Sprite_By_Texture(sf::Texture* cell_texture);
    void set_Sprite_By_Texture(std::string cell_texture_name);
    void set_Sprite_Origin(float x, float y);
    void set_Sprite_Position(float x, float y);
};


#endif //CELL_H