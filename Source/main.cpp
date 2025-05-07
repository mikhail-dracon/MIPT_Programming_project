#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "Texture_List.h"

// Константы
unsigned int SCREEN_WIDTH = 0;
unsigned int SCREEN_HEIGHT = 0;
float SCAIL_SPEED = 0.015; // Скорость зума
float SPEED = 40; // Скорость перемещения по карте
int FRAME_RATE = 60;
std::map<std::string, float> CONSTANTS; // Словарь констант для использования в функциях
std::string BUILDING_TEXTURE = ""; // Текстура создаваемой сущности
// int PLAYER_NUMBER = 1;
int MONEY = 1000;
void LoadUITextures() {
    std::vector<std::string> paths = {
            "../Textures/Warrior_right.png",
            "../Textures/Barracks.png",
            "../Textures/Mine.png",
            "../Textures/Miner_right.png"
    };
    for (const auto& path : paths) {
        sf::Texture tex;
        if (tex.loadFromFile(path)) {
            ui_textures.push_back(tex);
        }
    }
}

int main() {
    // Запуск окна
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    SCREEN_WIDTH = desktop.size.x;
    SCREEN_HEIGHT = desktop.size.y;
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Game");

    //Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("../Font/font.ttf")) {
        std::cerr << "Font not found!" << std::endl;
    }

    // Создание карты
    std::string texture_name = "../Textures/BasicLendPattern.png";
    Map Created_Map(20, texture_name);
    Created_Map.set_zero_x((SCREEN_HEIGHT/20)*8.0f);
    Created_Map.set_zero_y((SCREEN_WIDTH/2)*1.0f);
    CONSTANTS.insert({"SCAIL_SPEED", SCAIL_SPEED});
    CONSTANTS.insert({"SCREEN_HEIGHT", SCREEN_HEIGHT});
    CONSTANTS.insert({"SCREEN_WIDTH", SCREEN_WIDTH});

    // Создаем эталонный спрайт мир для установки глобальных констант
    sf::Texture cell_texture;
    if (!cell_texture.loadFromFile("../Textures/BasicLendPattern.png")) {
        std::cerr << "Failed to load cell texture!" << std::endl;
        return 1;
    }
    sf::Sprite Sprite(cell_texture);
    sf::FloatRect scaledBounds = (Sprite).getGlobalBounds();
    Created_Map.set_cell_width(scaledBounds.size.x);
    Created_Map.set_cell_height(scaledBounds.size.y);

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

    //Отрисовка иконок
    LoadUITextures();

    //Спрайты
    sf::Sprite warrior(ui_textures[0]);
    sf::Sprite barrack(ui_textures[1]);
    sf::Sprite mine(ui_textures[2]);
    sf::Sprite miner(ui_textures[3]);

    // Позиционирование
    barrack.setPosition((20.f/2048.f)*SCREEN_WIDTH, (100.f/1280.f)*SCREEN_HEIGHT);
    mine.setPosition(20.f/2048.f*SCREEN_WIDTH, 300.f/1280.f*SCREEN_HEIGHT);
    warrior.setPosition(1650.f/2048.f*SCREEN_WIDTH, 50.f/1280.f*SCREEN_HEIGHT);
    miner.setPosition(1550.f/2048.f*SCREEN_WIDTH, 250.f/1280.f*SCREEN_HEIGHT);
    warrior.setScale({1.5, 1.5});
    miner.setScale({1.7, 1.7});

    //Полупрозрачность
    barrack.setColor(sf::Color(255, 255, 255, 128));
    mine.setColor(sf::Color(255, 255, 255, 128));
    warrior.setColor(sf::Color(255, 255, 255, 128));
    miner.setColor(sf::Color(255, 255, 255, 128));

    //Шрифты под иконками
    sf::Text barrack_label("Press 1 to select", font, 20); // Надпись "Barrack", размер 20
    barrack_label.setFillColor(sf::Color::White); // Цвет текста
    barrack_label.setPosition(barrack.getPosition().x, barrack.getPosition().y + 150.f/1280.f*SCREEN_HEIGHT); // Под иконкой
    sf::Text mine_label("Press 2 to select", font, 20); // Надпись "Barrack", размер 20
    mine_label.setFillColor(sf::Color::White); // Цвет текста
    mine_label.setPosition(mine.getPosition().x, mine.getPosition().y + 200.f/1280.f*SCREEN_HEIGHT); // Под иконкой
    sf::Text warrior_label("Press 9 to select", font, 20); // Надпись "Barrack", размер 20
    warrior_label.setFillColor(sf::Color::White); // Цвет текста
    warrior_label.setPosition(warrior.getPosition().x + 50.f/2048.f*SCREEN_WIDTH, warrior.getPosition().y + 280.f/1280.f*SCREEN_HEIGHT); // Под иконкой
    sf::Text miner_label("Press 8 to select", font, 20); // Надпись "Barrack", размер 20
    miner_label.setFillColor(sf::Color::White); // Цвет текста
    miner_label.setPosition(miner.getPosition().x + 148.f/2048.f*SCREEN_WIDTH, miner.getPosition().y + 280.f/1280.f*SCREEN_HEIGHT);

    // Настраиваем игровые объекты
    Texture_List texture_list(&Created_Map, "Standart");
    Created_Map.get_Building_list()->Add_Building(0,0,"../Textures/FramePattern.png");
    Created_Map.get_Building_list()->Find_Building("FramePattern")->set_Sprite_Origin(Created_Map.get_cell_width()/2.0f, Created_Map.get_cell_height()*1.0f);
    Created_Map.get_Building_list()->Find_Building("FramePattern")->set_Sprite_Color(255, 255, 255, 150);

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
            Created_Map.Set_Sprite_Static_Position(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer(),i,j);
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
                Created_Map.Map_Scale(mouseWheelScrolled->delta, "Mouse", &CONSTANTS);
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    Created_Map.get_pressed_sell_position(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                }
            }
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && (Created_Map.get_zero_x())<SCREEN_HEIGHT/2.0f){
            Created_Map.set_zero_x(Created_Map.get_zero_x() + Created_Map.get_scale()*SPEED);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && (Created_Map.get_zero_x()>Created_Map.get_scale()*Created_Map.get_cell_height()*0.577*(-1.0f)*Created_Map.Get_Size())){
            Created_Map.set_zero_x(Created_Map.get_zero_x() - Created_Map.get_scale()*SPEED);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && (Created_Map.get_zero_y()+Created_Map.get_scale()*Created_Map.get_cell_width()*Created_Map.Get_Size()/2>0)){
            Created_Map.set_zero_y(Created_Map.get_zero_y() - Created_Map.get_scale()*SPEED);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && (Created_Map.get_zero_y()-Created_Map.get_scale()*Created_Map.get_cell_width()*Created_Map.Get_Size()/2<SCREEN_WIDTH)){
            Created_Map.set_zero_y(Created_Map.get_zero_y() + Created_Map.get_scale()*SPEED);
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) && (Created_Map.get_scale()<1)) {
            Created_Map.Map_Scale(1, "Keyboard", &CONSTANTS);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) && (Created_Map.get_scale()>0.2)) {
            Created_Map.Map_Scale(-1, "Keyboard", &CONSTANTS);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))) {
            Created_Map.set_Player_Number();
        }

        // Обработка выбора сущности
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            if (Created_Map.Check_Access("Barracks")){
                Created_Map.set_BUILDING_TEXTURE("../Textures/Barracks.png");
            }
            // Created_Map.set_BUILDING_TEXTURE("../Textures/Barracks.png");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0)) {
            if (Created_Map.Check_Access("grass") || Created_Map.Check_Access("Warrior")){
                Created_Map.set_BUILDING_TEXTURE("../Textures/grass.png");
            }
            // Created_Map.set_BUILDING_TEXTURE("../Textures/grass.png");
        }

        // Отрисовка
        window.clear(sf::Color::Black);
        // Отрисовка фона
        window.draw(Sky_Sprite);
        // Отрисовка клеточек
        for (unsigned int i = 0; i < Created_Map.Get_Size(); i++) {
            for (unsigned int j = 0; j < Created_Map.Get_Size(); j++) {
                Created_Map.Set_Sprite_Static_Position(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer(), i, j);
                Created_Map.Cells_Data[i][j]->set_Scale_Sprite(Created_Map.get_scale());
                window.draw(*(Created_Map.Cells_Data[i][j]->get_Sprite_Pointer()));
            }
        }
        // Отрисовка иконок
        window.draw(warrior);
        window.draw(barrack);
        window.draw(mine);
        window.draw(miner);
        window.draw(warrior_label);
        window.draw(barrack_label);
        window.draw(mine_label);
        window.draw(miner_label);
        
        // Отрисовка элементов из Building_List
        for (auto it = Created_Map.get_Building_list()->Buildings.begin(); it!= Created_Map.get_Building_list()->Buildings.end(); it++) {
            it->second->set_Sprite_Scale(Created_Map.get_scale());
            Created_Map.Set_Sprite_Static_Position(it->second->get_Sprite_Pointer(), it->second->get_x_coordinate(), it->second->get_y_coordinate());
            window.draw(*(it->second->get_Sprite_Pointer()));
        }

        window.display();
        sf::sleep(sf::milliseconds(1000/FRAME_RATE));

        // std::cout<<MONEY<<'\n';
    }

    std::cout << "Yep!" << std::endl;
}