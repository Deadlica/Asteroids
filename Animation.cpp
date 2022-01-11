//
// Created by samuel on 1/11/22.
//

#include "Animation.h"

Animation::Animation(): asteroidDied(false), speed(0.75), frame(0) {
    int width = 256, height = 256, totalFrames = 48;
    sprite.setOrigin(width / 2, height / 2);
    for(int i = 0; i < totalFrames; i++)
        frames.push_back(sf::IntRect(i * width, 0, width, height));
}

void Animation::update() {
    frame += speed;
    if(frames.size() > 0)
        sprite.setTextureRect(frames[int(frame)]);
}

void Animation::setPosition(float x, float y) {
    sprite.setPosition(x, y);

}

void Animation::setTexture(sf::Texture &t) {
    sprite.setTexture(t);
}

void Animation::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}