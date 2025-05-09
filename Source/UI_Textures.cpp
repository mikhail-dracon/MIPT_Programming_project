#include "UI_Textures.h"
#include <iostream>

// Создание текстовых меток (добавьте в конструктор после загрузки шрифта)
void UI_Textures::createTitles() {
    if (!font.getInfo().family.empty()) {
        ui_title.clear();

        const std::vector<std::string> labels = {
            "Press 1 to select (500)",
            "Press 2 to select",
            "Press 0 to select (200)",
            "Press 9 to select (500)"
        };

        for (const auto& label : labels) {
            sf::Text text(font);
            // text.setFont(font);  // Устанавливаем шрифт
            text.setString(label); // Устанавливаем текст
            text.setCharacterSize(20);
            ui_title.push_back(text);
        }
        std::cout << "TITLES CREATED" << std::endl;
    }
}

UI_Textures::UI_Textures() : SCREEN_WIDTH(2048.f), SCREEN_HEIGHT(1280.f) {
    std::vector<std::string> paths = {
            "../Textures/Barracks.png",
            "../Textures/Mine.png",
            "../Textures/Warrior.png",
            "../Textures/Miner.png"
    };

    // Загрузка текстур
    for (const auto& path : paths) {
        sf::Texture tex;
        if (tex.loadFromFile(path)) {
            tex_textures.push_back(tex);
        }
    }

    // Создание спрайтов
    for (const auto& tex : tex_textures) {
        ui_textures.emplace_back(tex);
    }
    if(font.openFromFile("../Font/font.ttf")){
        createTitles();
    }
    std::cout<<"UI_TEXTURES CREATED"<<std::endl;
    // createTitles();
}

// bool UI_Textures::loadFont(const std::string& fontPath) {
//     std::cout<<"FONT LOADED"<<std::endl;
//     return font.openFromFile(fontPath);
// }

std::vector<sf::Sprite>* UI_Textures::get_ui_textures() {
    return &ui_textures;
}

// std::vector<sf::Sprite>* UI_Textures::get_ui_textures() {
    // return &ui_textures;
// }

std::vector<sf::Text>* UI_Textures::get_ui_title() {
    return &ui_title;
}

UI_Textures::~UI_Textures() {
    tex_textures.clear();
    ui_textures.clear();
    ui_title.clear();
}

void UI_Textures::set_transparency(int transparency) {
    for (auto& sprite : ui_textures) {
        sprite.setColor(sf::Color(255, 255, 255, transparency));
    }
}

void UI_Textures::set_position_textures() {
    if(ui_textures.size() < 4) return;

    ui_textures[0].setPosition({20.f/2048.f * SCREEN_WIDTH, 100.f/1280.f * SCREEN_HEIGHT});
    ui_textures[1].setPosition({20.f/2048.f * SCREEN_WIDTH, 300.f/1280.f * SCREEN_HEIGHT});
    ui_textures[2].setPosition({1650.f/2048.f * SCREEN_WIDTH, 50.f/1280.f * SCREEN_HEIGHT});
    ui_textures[3].setPosition({1550.f/2048.f * SCREEN_WIDTH, 250.f/1280.f * SCREEN_HEIGHT});
    ui_textures[2].setScale({1.5f, 1.5f});
    ui_textures[3].setScale({1.7f, 1.7f});
}

void UI_Textures::set_color_title() {
    for(auto& title : ui_title) {
        title.setFillColor(sf::Color::White);
    }
}

void UI_Textures::set_position_title() {
    if(ui_textures.size() < 4 || ui_title.size() < 4) return;

    ui_title[0].setPosition({ui_textures[0].getPosition().x,
                            ui_textures[0].getPosition().y + 150.f/1280.f*SCREEN_HEIGHT});

    ui_title[1].setPosition({ui_textures[1].getPosition().x,
                            ui_textures[1].getPosition().y + 200.f/1280.f*SCREEN_HEIGHT});

    ui_title[2].setPosition({ui_textures[2].getPosition().x + 50.f/2048.f*SCREEN_WIDTH,
                            ui_textures[2].getPosition().y + 280.f/1280.f*SCREEN_HEIGHT});

    ui_title[3].setPosition({ui_textures[3].getPosition().x + 148.f/2048.f*SCREEN_WIDTH,
                            ui_textures[3].getPosition().y + 280.f/1280.f*SCREEN_HEIGHT});
    std::cout<<"UI_TITLES POSITIONISED"<<std::endl;
}

void UI_Textures::set_screen_size(float width, float height) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    set_position_textures();
    set_transparency(128);
    set_position_title();
    set_color_title();
}