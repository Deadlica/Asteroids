//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_OBJECT_H
#define SFML_GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <utility>
#include <string>
#include <ctime>
#include <cmath>
#include "Animation.h"


//! Abstract base class for all moving entities.
class Object {
public:
    /**
     * Default constructor.
     * @param x x-coordinate position.
     * @param y y-coordinate position.
     * @param angle Objects starting rotation.
     * @param radius Objects radius.
     */
    Object(float x, float y, float angle, float radius);

    /**
     * Destructor. Destroys the object, all its children.
     */
    virtual ~Object() = default;

    /**
     * Updates the objects private members.
     */
    virtual void update() = 0;

    /**
     * Checks if object has collided with another object.
     * @param object Other object to check collision with.
     * @return True if there is a collision.
     */
    virtual bool checkCollision(std::unique_ptr<Object> &object);

    /**
     * Draws the object to a window.
     * @param window The window to draw the object on.
     */
    virtual void draw(sf::RenderWindow &window);

    /**
     * Gives the object an identifying name.
     * @param name The name to be given.
     */
    void setName(std::string name);

    /**
     * Tells the object its windows borders.
     * @param width Window width.
     * @param height Window height.
     */
    virtual void setBorder(const unsigned int width, const unsigned int height);

    /**
     * Sets the objects x, y coordinate
     * @param x x-coordinate
     * @param y y-coordinate
     */
    void setPosition(const float x, const float y);

    // Getters
    /**
     * Gets the current amount of objects created.
     * @return Reference to amount of given object that's alive.
     */
    virtual int& GetCount() const = 0;

    /**
     * Gets the objects sprite.
     * @return Reference to the sprite member.
     */
    sf::Sprite& GetSprite();

    /**
     * Gets the objects name.
     * @return The objects name.
     */
    const std::string GetName() const;

    /**
     * Gets the objects coordinate position.
     * @return A pair of its x, y-coordinate.
     */
    const std::pair<float, float> GetPosition() const;

    /**
     * Gets the objects rotation angle.
     * @return The objects rotation angle.
     */
    const float GetAngle() const;

    /**
     * Gets the objects radius.
     * @return The objects radius.
     */
    const float GetRadius() const;

    /**
     * Checks if the object is alive.
     * @return True if the object is alive.
     */
    bool Alive();

    /**
     * Kills the object.
     */
    void kill();

protected:
    /**
     * Checks the objects coordinates in relation to the windows size, resets it if the object is out of bounds
     */
    void checkBorderCoordinates();
    sf::Sprite sprite;
    //Coordinates, offset coordinates
    std::pair<float, float> coords, coordsDelta;
    float radius, angle, spriteWidth, spriteHeight;
    bool life;
    std::string name;
    static unsigned int windowWidth, windowHeight;
private:

};


#endif //SFML_GAME_OBJECT_H
