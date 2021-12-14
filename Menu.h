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
#include <vector>
#include <iostream>
#include <fstream>

class Menu {
public:
    Menu(const unsigned int width, const unsigned int height);

    enum Button {PLAY = 1, GAMEMODE = 2, QUIT = 3, ASTEROIDS = 4, BOSS = 5, WIN = 6, LOSE = 7, SUBMIT = 8, BACK = 9};

    void run(sf::RenderWindow &window);
    void displayWin(sf::RenderWindow &window);
    void displayLoss(sf::RenderWindow &window, unsigned int score);


    const int GetPosition() const;
    const unsigned int GetDifficulty() const;

private:
    void draw(sf::RenderWindow &window);

    void up();
    void down();
    void hideButtons();
    void showMainMenu();
    void showSubMenu(sf::RenderWindow &window);
    void submitScore();

    void createButtons();
    void initButton(std::string text, const unsigned int x, const unsigned int y);
    void initText(sf::RectangleShape rect, sf::Text &label, std::string text, const unsigned int x, unsigned int y);
    void initRect(sf::RectangleShape &rect, const unsigned int x, const unsigned int y);
    void initSounds();
    unsigned int position, difficulty, score;
    unsigned int windowWidth, windowHeight;

    sf::Font textFont;
    std::vector<std::pair<sf::RectangleShape, sf::Text>> buttons;
    sf::Music theme;
    sf::SoundBuffer buffer1, buffer2;
    sf::Sound hover, enter;
    sf::Texture tBackground;
    sf::Sprite sBackground;

};


#endif //SFML_GAME_MENU_H
