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

    enum Button {PLAY = 1, GAMEMODE = 2, QUIT = 3,
                 ASTEROIDS = 4, BOSS = 5, WIN = 6,
                 LOSE = 7, SUBMIT = 8, BACK = 9};

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
    void showGamemodeMenu(sf::RenderWindow &window);
    void topScoresPlacement();
    void fetchTopScores();
    void submitScore();
    void keyAction(sf::RenderWindow &window, sf::Event &event);
    void checkPosition(sf::RenderWindow &window);

    void createButtons();
    void initButton(std::string text, const unsigned int x, const unsigned int y);
    void initText(sf::RectangleShape rect, sf::Text &label, std::string text, const unsigned int x, unsigned int y);
    void initRect(sf::RectangleShape &rect, const unsigned int x, const unsigned int y);
    void initSounds();
    unsigned int position, difficulty, score;
    unsigned int windowWidth, windowHeight;
    bool startGame;

    sf::Font textFont;
    std::vector<std::pair<sf::RectangleShape, sf::Text>> buttons;
    std::vector<sf::Text> topScores;
    sf::Music theme;
    sf::SoundBuffer buffer1, buffer2;
    sf::Sound hover, enter;
    sf::Texture tBackground;
    sf::Sprite sBackground;
};

struct createScore {
    std::vector<int> scores;
    int index = 0;

    sf::Text operator()() {
        sf::Text text;
        text.setString(std::to_string(scores[index]));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        return text;
    }
};

struct showMain {
    bool doOnce = true;
    void operator()(std::pair<sf::RectangleShape, sf::Text> &b) {
        if(doOnce) {
            b.second.setFillColor(sf::Color::White);
            doOnce = false;
        }
        if(b.second.getString() == "Play" || b.second.getString() == "Gamemode" || b.second.getString() == "Quit") {
            b.first.setOutlineColor(sf::Color(54, 173, 207 ,100));
            b.second.setFillColor(sf::Color::White);
        }
    }
};

struct showGamemode {
    void operator()(std::pair<sf::RectangleShape, sf::Text> &b) {
        if(b.second.getString() == "Asteroids" || b.second.getString() == "Boss") {
            b.first.setOutlineColor(sf::Color(54, 173, 207 ,100));
            b.second.setFillColor(sf::Color::White);
        }
        else if(b.second.getString() == "ASTEROIDS")
            b.second.setFillColor(sf::Color::Transparent);
    }
};

#endif //SFML_GAME_MENU_H
