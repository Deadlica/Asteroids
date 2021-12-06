//
// Created by samuel on 12/5/21.
//

#ifndef SFML_GAME_GAME_H
#define SFML_GAME_GAME_H

#include "Object.h"
#include "Player.h"
#include "Asteroid.h"
#include "Projectile.h"
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

    //Game objects

    //Textures
    Player spaceship;
    sf::Texture tBackground;

    //Sprites
    sf::Sprite sBackground;

    //Container for objects
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<Projectile>> projectiles;

    //Game music
    sf::Music gameMusic;
    std::string Space_Invaders = "sounds/Teminite & MDK - Space Invaders [Monstercat Remake].ogg";
    std::string Arcade_Bit_Rush = "sounds/Bit Rush - Arcade 2015 _ Login Screen - League of Legends.ogg";

    void centerWindowPosition();

    //Asteroids
    void generateAsteroids();
    void updateAsteroids();
    void drawAsteroids();

    //Projectiles
    void generateProjectile();
    void updateProjectiles();
    void drawProjectiles();

    //Player
    void updatePlayerPosition();
    bool isAnyKeyPressed();

    //Initialization
    void initTextures();
    void initSprites();
};


#endif //SFML_GAME_GAME_H
