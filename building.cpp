#include "building.h"

building::building(int x, int y, std::string Building_Texture) {
    x_coordinate = x;
    y_coordinate = y;
    Scale = 1;
    Texture.loadFromFile(Building_Texture);
    Sprite = new sf::Sprite(Texture);
}

building::~building() {
    delete Sprite;
}

int building::get_x_coordinate() const{
    return x_coordinate;
}

int building::get_y_coordinate() const{
    return y_coordinate;
}

void building::set_x_coordinate(int value){
    x_coordinate = value;
}

void building::set_y_coordinate(int value){
    y_coordinate = value;
}

std::string building::get_Texture_Name() const {
    return Texture_Name;
}

sf::Sprite* building::get_Sprite_Pointer() const{
    return Sprite;
}

void building::set_Sprite_By_Texture(sf::Texture* building_texture) {
    Texture = *building_texture;
    delete Sprite;
    Sprite = new sf::Sprite(Texture);
}

void building::set_Sprite_By_Texture(std::string building_texture_name) {
    Texture.loadFromFile(building_texture_name);
    delete Sprite;
    Sprite = new sf::Sprite(Texture);
}


void building::set_Sprite_Origin(float x, float y) {
    (*Sprite).setOrigin({x, y});
}

void building::set_Sprite_Position(float x, float y) {
    (*Sprite).setPosition({x, y});
}

void building::set_Sprite_Scale(float scale) {
    (*Sprite).setScale({scale, scale});
}

void building::set_Sprite_Color(int r, int g, int b, int a) {
    sf::Color color = sf::Color(r, g, b, a);
    (*Sprite).setColor(color);
}