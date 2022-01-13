//
// Created by samuel on 12/11/21.
//

#ifndef SFML_GAME_ENEMY_H
#define SFML_GAME_ENEMY_H

#include "Player.h"
#include "Projectile.h"
#include <chrono>

//! Object that represents the enemy boss. It inherits from Player which inherits from Object. It handles its own movement based on where the player is and attacks everytime its direction is changed.
class Enemy: public Player {
public:
    /**
     * Default constructor.
     */
    Enemy();

    /**
     * Adjusts its rotation based on the players position, checks if it's outside of the window, updates animation frame.
     */
    void update() override;

    /**
     * After a random time it will change direction to move in.
     * @return True if the direction has been changed.
     */
    bool changeDirection();

    /**
     * Checks if it's time to update the animation frame.
     */
    void updateAnimation();

    /**
     * Updates the enemy's texture when its taken damage.
     */
    void damageAnimation();

    /**
     * Makes the enemy shoot 3 projectiles aimed at the player.
     * @param objects The container holding all the instantiated objects (projectiles, asteroids etc...).
     * @param t The texture of the projectile.
     */
    void attack(std::vector<std::unique_ptr<Object>> &objects, sf::Texture &t);

    /**
     * Gives the enemy the current location of the player.
     * @param x The players x-coordinate
     * @param y The players y-coordinate
     */
    void GetPlayerCoordinates(float x, float y);

    /**
     * Checks if the enemy has been hit by a projectile shot by the player.
     * @param object The container holding all the instantiated objects.
     * @return True if the enemy has been hit by a projectile.
     */
    bool checkCollision(std::unique_ptr<Object> &object) override;

    /**
     * Gets the enemy's current health.
     * @return The enemy's health.
     */
    const unsigned int GetHP() const;

private:
    std::pair<float, float> playerCoords;
    unsigned int HP;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, animationStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop, animationStop;
    std::chrono::duration<double> time, animationTime;
};


#endif //SFML_GAME_ENEMY_H
