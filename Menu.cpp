//
// Created by samuel on 12/9/21.
//

#include "Menu.h"

Menu::Menu() {

}

void Menu::start() {

}

void Menu::stop() {

}

void Menu::draw() {

}

void Menu::initButtons() {
    textFont.loadFromFile("fonts/Symtext.ttf");
    title.first.setSize(sf::Vector2f(200, 50));
    title.second.setFont(textFont);
    title.second.setString("Asteroids");

}
