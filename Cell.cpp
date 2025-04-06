#include "Cell.h"

Cell::Cell(int x, int y, std::string Map_Texture) {
    x_coordinate = x;
    y_coordinate = y;
    Texture.loadFromFile(Map_Texture);
    Sprite = new sf::Sprite(Texture);
}

Cell::~Cell() {}
int Cell::get_x_coordinate() const{
    return x_coordinate;
    delete Sprite;
}

int Cell::get_y_coordinate() const{
    return y_coordinate;
}

std::string Cell::get_Texture() const {
    return Texture_Name;
}

void Cell::set_Sprite(sf::Texture* cell_texture) {
    Texture = *cell_texture;
    delete Sprite;
    Sprite = new sf::Sprite(Texture);
}

sf::Sprite* Cell::get_Sprite() const{
    return Sprite;
}

void Cell::set_Sprite_Origin(float x, float y) {
    (*Sprite).setOrigin({x, y});
}

void Cell::set_Sprite_Position(float x, float y) {
    (*Sprite).setPosition({x, y});
}