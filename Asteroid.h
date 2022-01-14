//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_ASTEROID_H
#define SFML_GAME_ASTEROID_H

#include "Object.h"
#include "Animation.h"

//! Object that represents an asteroid. It inherits from Object.
class Asteroid : public Object {
public:
    /**
     * Default constructor.
     * @param t The texture for the asteroid.
     * @param x x-coordinate position.
     * @param y y-coordinate position.
     * @param angle Asteroids starting rotation.
     * @param radius Asteroids radius.
     * @param playerPosition The players coordinates.
     */
    Asteroid(sf::Texture &t, float x, float y, float angle, float radius, std::pair<float, float> playerPosition);

    /**
     * Gets the amount of asteroids that are currently alive.
     * @return Reference of the counter.
     */
    int& GetCount() const override;

    /**
     * Updates the asteroids position, checks if it is outside of the window.
     */
    void update() override;

    /**
     * Draws the asteroid to a window.
     * @param window The window to draw the asteroid on.
     */
    void draw(sf::RenderWindow &window) override;

    /**
     * Makes sure that the asteroid doesn't spawn on the player.
     * @param playerPosition The players coordinates.
     */
    void dontSpawnOnPlayer(std::pair<float, float> &playerPosition);

    /**
     * Counter for the amount of instantiated asteroids.
     */
    static int count;
private:
    Animation rock;
};


#endif //SFML_GAME_ASTEROID_H
