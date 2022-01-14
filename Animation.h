//
// Created by samuel on 1/11/22.
//

#ifndef SFML_GAME_ANIMATION_H
#define SFML_GAME_ANIMATION_H

#include "SFML/Graphics.hpp"

//! This acts as an animated sequence
class Animation {
public:
    /**
     * Default constructor.
     */
    Animation() = default;

    /**
     * Parameterized constructor.
     * @param width The width of the frames.
     * @param height The height of the frames.
     * @param speed The update speed of the frames.
     * @param totalFrames The total frames for the animation.
     * @param loop If the animation should be looped.
     */
    Animation(int width, int height, float speed, int totalFrames, bool loop = false);

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
    bool loop;
    std::pair<float, float> coords;
    std::vector<sf::IntRect> frames;
};


#endif //SFML_GAME_ANIMATION_H
