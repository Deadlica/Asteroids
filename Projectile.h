//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_PROJECTILE_H
#define SFML_GAME_PROJECTILE_H

#include "Object.h"
/**
 * Object that represents a bullet/projectile. It inherit from Object, has an angle and speed etc...
 */
class Projectile : public Object {
public:
    /**
     * Default constructor.
     * @param x x-coordinate position.
     * @param y y-coordinate position.
     * @param angle Projectiles starting rotation.
     * @param radius Projectiles radius.
     * @param speed Projectiles speed.
     */
    Projectile(float x, float y, float angle, float radius, float speed);

    /**
     * Gets the amount of projectiles that are currently alive.
     * @return Reference of the counter.
     */
    int& GetCount() const override;

    /**
     * Checks the projectiles current position, updates it given its speed. It also checks if the projectile is out of bounds.
     */
    void update() override;

    /**
     * Counter for the amount of instantiated projectiles.
     */
    static int count;
private:
    static constexpr float DTR = 0.0174532925;
    float speed;
    sf::SoundBuffer buffer;
    sf::Sound gunBlast;
};


#endif //SFML_GAME_PROJECTILE_H
