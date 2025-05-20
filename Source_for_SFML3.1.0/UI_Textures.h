#ifndef BUILDING_H_UI_TEXTURES_H
#define BUILDING_H_UI_TEXTURES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class UI_Textures {
    sf::Font font;
    std::vector<sf::Texture> tex_textures;
    std::vector<sf::Sprite> ui_textures;
    std::vector<sf::Text> ui_title;
    float SCREEN_WIDTH;
    float SCREEN_HEIGHT;
    std::vector<sf::Text> infoTexts;
    sf::RectangleShape infoBox;
    sf::RectangleShape texBox;
    sf::RectangleShape toggleButton;    // Кнопка-рамка
    sf::RectangleShape popupWindow;     // Всплывающее окно
    sf::Text popupText;                 // Текст внутри окна
    sf::Text buttonLabel; // Надпись на кнопке


    void createTitles();

public:
    UI_Textures();
    ~UI_Textures();

    std::vector<sf::Sprite>* get_ui_textures();
    std::vector<sf::Text>* get_ui_title();
    std::vector<sf::Text>& get_info_texts();
    sf::RectangleShape& get_info_box();
    sf::RectangleShape& get_tex_box();

    void set_screen_size(float width, float height);
    void set_position_textures();
    void set_position_title();
    void set_color_title();
    void set_transparency(int transparency);

    void createInfoPanel();
    void updateInfoPanel(int money, int currentPlayer, int turnNumber);

    void handleClick(int mouseX, int mouseY); // Обработка кликов
    void updatePopupText(const std::string& text); // Обновление текста окна
    sf::RectangleShape& get_toggle_button() { return toggleButton; }
    sf::RectangleShape& get_popup_window() { return popupWindow; }
    sf::Text& get_button_label() { return buttonLabel; }
    sf::Text& get_popup_text() { return popupText; }
    bool isPanelVisible;
    void updateButtonLabel(const std::string& text);
};

#endif