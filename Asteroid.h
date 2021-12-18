//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_ASTEROID_H
#define SFML_GAME_ASTEROID_H

#include "Object.h"
/**
 * Object that represents an asteroid. It inherit from Object.
 */
class Asteroid : public Object {
public:
    /**
     * Default constructor.
     * @param x x-coordinate position.
     * @param y y-coordinate position.
     * @param angle Asteroids starting rotation.
     * @param radius Asteroids radius
     */
    Asteroid(float x, float y, float angle, float radius);

    /**
     * Gets the amount of asteroids that are currently alive.
     * @return Reference of the counter.
     */
    int& GetCount() const override;

    /**
     * Updates the asteroids position, checks if it is out of bounds.
     */
    void update() override;

    /**
     * Counter for the amount of instantiated asteroids.
     */
    static int count;
private:


};


#endif //SFML_GAME_ASTEROID_H
