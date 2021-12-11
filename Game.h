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

class Game {
public:
    //Constructor
    Game(const unsigned int width, const unsigned int height);

    //Accessors
    const bool running() const;

    //Functions
    void pollEvents();
    void update();
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

    void centerWindowPosition();
    void checkCollision();
    bool isCollision(std::vector<std::unique_ptr<Object>>::value_type &p, std::vector<std::unique_ptr<Object>>::value_type &a);
    void checkPlayerCollision();
    void clearGame();

    //Objects
    void generateAsteroids();
    void generateProjectile();
    void generateBoss();
    void updateObjects();
    void drawObjects();

    //Player
    void updatePlayerPosition();
    bool isAnyKeyPressed();

    //Initialization
    void initTextures();
    void initSprites();
    void initSounds();
};


#endif //SFML_GAME_GAME_H
