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
/**
 * This class represents all the games menus, states. Such as the start menu, sub menus, handling navigation throughout all the different states etc...
 */
class Menu {
public:
    /**
     * Default constructor
     * @param width The width of the menu.
     * @param height The height of the menu.
     */
    Menu(const unsigned int width, const unsigned int height);

    /**
     * Enum for all menu's button positions.
     */
    enum Button {PLAY = 1, GAMEMODE = 2, QUIT = 3,
                 ASTEROIDS = 4, BOSS = 5, WIN = 6,
                 LOSE = 7, SUBMIT = 8, BACK = 9};

    /**
     * Starts the menu loop.
     * @param window The window to run the menu on.
     */
    void run(sf::RenderWindow &window);

    /**
     * Displays a winning menu state.
     * @param window The window to display it on.
     */
    void displayWin(sf::RenderWindow &window);

    /**
     * Displays a losing menu state.
     * @param window The window to display it on.
     * @param score The score that the player got during the game.
     */
    void displayLoss(sf::RenderWindow &window, unsigned int score);

    /**
     * Gets the current button position in the menu.
     * @return The Button enum representing the current button position.
     */
    const Button GetPosition() const;

    /**
     * Gets the current difficulty setting
     * @return The Button enum representing the current difficulty setting.
     */
    const Button GetDifficulty() const;

private:
    void draw(sf::RenderWindow &window);

    void up();
    void down();
    void hideButtons();
    void showMainMenu();
    void showGamemodeMenu(sf::RenderWindow &window);
    std::vector<int> fetchScoresFromFile();
    void generateTopScoresText();
    void submitScore();
    void keyAction(sf::RenderWindow &window, sf::Event &event);
    void checkPosition(sf::RenderWindow &window);

    void createButtons();
    void initButton(std::string text, const unsigned int x, const unsigned int y);
    void initText(sf::RectangleShape rect, sf::Text &label, std::string text, const unsigned int x, unsigned int y);
    void initRect(sf::RectangleShape &rect, const unsigned int x, const unsigned int y);
    void initSounds();
    Button position, difficulty;
    unsigned int score;
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

/**
 * Predicate for displaying the Main menu buttons.
 */
struct showMain {
    bool doOnce = true;
    /**
     * The operator() which is used by std::for_each function.
     * @param b The std::pair which is seen as a button.
     */
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

/*
 * Predicate functor for displaying the Gamemode menu buttons.
 */
struct showGamemode {
    /**
     * The operator() which is used by std::for_each function.
     * @param b The std::pair which is seen as a button.
     */
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
