//
// Created by samuel on 1/11/22.
//

#ifndef SFML_GAME_ANIMATION_H
#define SFML_GAME_ANIMATION_H

#include "SFML/Graphics.hpp"


class Animation {
public:
    Animation();

    void update();

    void setPosition(float x, float y);
    void setTexture(sf::Texture &t);

    void draw(sf::RenderWindow &window);

    float frame;

private:
    bool asteroidDied;
    sf::Sprite sprite;
    float speed;
    std::pair<float, float> coords;
    std::vector<sf::IntRect> frames;
};


#endif //SFML_GAME_ANIMATION_H
