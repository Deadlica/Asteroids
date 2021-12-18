//
// Created by samuel on 12/5/21.
//

#ifndef SFML_GAME_GAME_H
#define SFML_GAME_GAME_H

#include "Object.h"
#include "Player.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "Menu.h"
#include "Enemy.h"
#include <vector>
#include <algorithm>
/**
 * Can be considered a wapper class or game engine for the Asteroids game. It's responsible for all states of the game, updating, rendering. As well as handling the menu, keyboard inputs.
 */
class Game {
public:
    /**
     * Default constructor
     * @param width Width of the application window(in pixels).
     * @param height Height of the application window(in pixels).
     */
    Game(const unsigned int width, const unsigned int height);

    /**
     * Checks if the application window is open.
     * @return True if the window isn't closed.
     */
    const bool running() const;

    //Functions
    /**
     * Handles all keyboard inputs, mouse clicks etc..
     */
    void pollEvents();

    /**
     * Updates all members, objects belonging to the Game class.
     */
    void update();

    /**
     * Renders all the Game objects to the application window.
     */
    void render();
private:
    //Members
    sf::RenderWindow window;
    sf::Event event;
    sf::Text score;
    int points = 0;
    sf::Font textFont;
    Menu menu;

    //Textures
    //Player spaceship;
    std::unique_ptr<Player> spaceship;
    std::unique_ptr<Enemy> enemy;
    sf::Texture tBackground;

    //Sprites
    sf::Sprite sBackground;

    //Container for objects
    std::vector<std::unique_ptr<Object>> objects;

    //Game music
    sf::Music gameMusic;
    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer2;
    sf::Sound asteroidDeath;
    sf::Sound projectileFired;
    std::string Space_Invaders = "sounds/Teminite & MDK - Space Invaders [Monstercat Remake].ogg";
    std::string Arcade_Bit_Rush = "sounds/Bit Rush - Arcade 2015 _ Login Screen - League of Legends.ogg";
    std::string cigg_pk = "sounds/cigg_pk.ogg";
    std::string Hopes_And_Dreams = "sounds/Undertale Ost - 087 - Hopes and Dreams.ogg";

    // State checkers
    void centerWindowPosition();
    void checkObjectCollision();
    void checkPlayerCollision();
    void startGame();
    void clearGame();

    //Objects
    void generateAsteroids();
    void generateProjectile();
    void generatePlayer();
    void generateBoss();
    void updateObjects();
    void updateEnemy();
    void updateScore();
    void drawObjects();

    //Player
    void updatePlayer();
    bool isAnyKeyPressed();

    //Initialization
    void initTextures();
    void initSprites();
    void initSounds();
};


#endif //SFML_GAME_GAME_H
