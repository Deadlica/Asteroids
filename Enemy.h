//
// Created by samuel on 12/11/21.
//

#ifndef SFML_GAME_ENEMY_H
#define SFML_GAME_ENEMY_H

#include "Player.h"
#include "Projectile.h"
#include <chrono>
/**
 * Object that represents a the enemy boss. It inherit from Object and Player. It handles its own movement based on where the player is and attacks everytime its direction is updated.
 */
class Enemy: public Player {
public:
    /**
     * Default constructor.
     */
    Enemy();

    /**
     * Adjusts the angle based on the players position, checks out of bounds, updates animation frame.
     */
    void update() override;

    /**
     * After a random time it gives the enemy a new direction to move in.
     * @return True if the direction has been changed.
     */
    bool changeDirection();

    /**
     * Checks if its time to update the animation frame.
     */
    void updateAnimation();

    /**
     * Updates the enemy's texture when its taken damage.
     */
    void damageAnimation();

    /**
     * Makes the enemy shoot 3 projectiles aimed at the player.
     * @param objects The container holding all the instantiated objects (projectiles, asteroids etc...).
     */
    void attack(std::vector<std::unique_ptr<Object>> &objects);

    /**
     * Gives the enemy the current location of the player.
     * @param x The players x-coordinate
     * @param y The players y-coordinate
     */
    void GetPlayerCoordinates(float x, float y);

    /**
     * Checks if the enemy has been hit by a projectile from the player.
     * @param object The list holding all the instantiated objects.
     * @return True if the enemy has been hit by a bullet
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
