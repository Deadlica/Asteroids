//
// Created by samuel on 12/9/21.
//

#ifndef SFML_GAME_MENU_H
#define SFML_GAME_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>

class Menu {
public:
    Menu();

    void start();
    void stop();
    void draw();

private:
    void initButtons();

    sf::Font textFont;
    std::pair<sf::RectangleShape, sf::Text> title, play, quit, retry, submitHighscore;

};


#endif //SFML_GAME_MENU_H
