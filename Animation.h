//
// Created by samuel on 1/11/22.
//

#ifndef SFML_GAME_ANIMATION_H
#define SFML_GAME_ANIMATION_H

#include "SFML/Graphics.hpp"


class Animation {
public:
    /**
     * Default constructor.
     */
    Animation();

    /**
     * Updates the frames of the animation.
     */
    void update();

    /**
     * Sets the position of where the explosion should display.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    void setPosition(float x, float y);

    /**
     * Sets a texture for the animation.
     * @param t The texture to be set.
     */
    void setSpriteTexture(sf::Texture &t);

    /**
     * Draws the animation frames to a window.
     * @param window The window to draw on.
     */
    void draw(sf::RenderWindow &window);

    /**
     * The current frame of the animaiton.
     */
    float frame;

private:
    sf::Sprite sprite;
    float speed;
    std::pair<float, float> coords;
    std::vector<sf::IntRect> frames;
};


#endif //SFML_GAME_ANIMATION_H
