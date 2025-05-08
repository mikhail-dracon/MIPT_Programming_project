#include "UI_Textures.h"

UI_Textures::UI_Textures() : SCREEN_WIDTH(2048.f), SCREEN_HEIGHT(1280.f) {
    std::vector<std::string> paths = {
            "../Textures/Barracks.png",
            "../Textures/Mine.png",
            "../Textures/Warrior_right.png",
            "../Textures/Miner_right.png"
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
    if(font.loadFromFile("../Font/font.ttf")){
        createTitles();
    }
}

bool UI_Textures::loadFont(const std::string& fontPath) {
    return font.loadFromFile(fontPath);
}

// Создание текстовых меток (добавьте в конструктор после загрузки шрифта)
void UI_Textures::createTitles() {
    if(ui_title.empty()) {
        ui_title.resize(4);
        ui_title[0].setString("Press 1 to select");
        ui_title[1].setString("Press 2 to select");
        ui_title[2].setString("Press 0 to select");
        ui_title[3].setString("Press 9 to select");

        for(auto& text : ui_title) {
            text.setFont(font);
            text.setCharacterSize(20);
        }
    }
}

const std::vector<sf::Sprite>* UI_Textures::get_ui_textures() const {
    return &ui_textures;
}

std::vector<sf::Sprite>* UI_Textures::get_ui_textures() {
    return &ui_textures;
}

const std::vector<sf::Text>* UI_Textures::get_ui_title() const {
    return &ui_title;
}

UI_Textures::~UI_Textures() {
    tex_textures.clear();
    ui_textures.clear();
    ui_title.clear();
}

void UI_Textures::set_screen_size(float width, float height) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    set_position_textures();
    set_transparency(128);
    set_position_title();
    set_color_title();
}

void UI_Textures::set_transparency(int transparency) {
    for (auto& sprite : ui_textures) {
        sprite.setColor(sf::Color(255, 255, 255, transparency));
    }
}

void UI_Textures::set_position_textures() {
    if(ui_textures.size() < 4) return;

    ui_textures[0].setPosition(20.f/2048.f * SCREEN_WIDTH, 100.f/1280.f * SCREEN_HEIGHT);
    ui_textures[1].setPosition(20.f/2048.f * SCREEN_WIDTH, 300.f/1280.f * SCREEN_HEIGHT);
    ui_textures[2].setPosition(1650.f/2048.f * SCREEN_WIDTH, 50.f/1280.f * SCREEN_HEIGHT);
    ui_textures[3].setPosition(1550.f/2048.f * SCREEN_WIDTH, 250.f/1280.f * SCREEN_HEIGHT);
    ui_textures[2].setScale(1.5f, 1.5f);
    ui_textures[3].setScale(1.7f, 1.7f);
}

void UI_Textures::set_color_title() {
    for(auto& title : ui_title) {
        title.setFillColor(sf::Color::White);
    }
}

void UI_Textures::set_position_title() {
    if(ui_textures.size() < 4 || ui_title.size() < 4) return;

    ui_title[0].setPosition(ui_textures[0].getPosition().x,
                            ui_textures[0].getPosition().y + 150.f/1280.f*SCREEN_HEIGHT);

    ui_title[1].setPosition(ui_textures[1].getPosition().x,
                            ui_textures[1].getPosition().y + 200.f/1280.f*SCREEN_HEIGHT);

    ui_title[2].setPosition(ui_textures[2].getPosition().x + 50.f/2048.f*SCREEN_WIDTH,
                            ui_textures[2].getPosition().y + 280.f/1280.f*SCREEN_HEIGHT);

    ui_title[3].setPosition(ui_textures[3].getPosition().x + 148.f/2048.f*SCREEN_WIDTH,
                            ui_textures[3].getPosition().y + 280.f/1280.f*SCREEN_HEIGHT);
}