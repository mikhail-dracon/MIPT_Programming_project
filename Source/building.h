#ifndef BUILDING_H
#define BUILDING_H
#include <string>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
// #include "Map.h"

// Этого дурачка надо еще причесывать, но самые необходимые вещи он уже умеет
// При всем остальном, он не знает своего хозяина, хозяина знает только класс Building_List
class building {
protected:
    int x_coordinate;
    int y_coordinate;
    float Scale;
    sf::Sprite* Sprite;
    sf::Texture Texture;
    std::string Texture_Name;
    int health;
    int owner_id; // здесь имеется в виду номер игрока или бота, необходимо для функции захвата
    bool ability_unit; // возможность создание юнитов
    bool ability_money; // наличие денег
    //int unit_limit;
    //int create_units; // количество юнитов, созданных одним объектом класса
public:
    building(int x, int y, std::string texture);
    ~building();
    int get_x_coordinate() const;
    int get_y_coordinate() const;
    void set_x_coordinate(int value);
    void set_y_coordinate(int value);
    std::string get_Texture_Name() const;
    sf::Sprite* get_Sprite_Pointer() const;
    void set_Sprite_By_Texture(sf::Texture* building_texture);
    void set_Sprite_By_Texture(std::string building_texture_name);
    void set_Sprite_Origin(float x, float y);
    void set_Sprite_Position(float x, float y);
    void set_Sprite_Scale(float scale);
    void set_Sprite_Color(int r, int g, int b, int a);
    //bool Create_Unit(); // создание юнита
    void set_health(int delta_health); // лечение/по ебалу получение
    //bool Can_Create_Unit() const; // проверка лимита
    int get_owner_id() const;
    int get_health() const;

};



#endif //BUILDING_H