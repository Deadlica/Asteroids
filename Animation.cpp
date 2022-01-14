//
// Created by samuel on 1/11/22.
//

#include "Animation.h"

Animation::Animation(int width, int height, float speed, int totalFrames, bool loop): speed(speed), frame(0), loop(loop) {
    sprite.setOrigin(width / 2, height / 2);
    for(int i = 0; i < totalFrames; i++)
        frames.push_back(sf::IntRect(i * width, 0, width, height));
}

void Animation::update() {
    frame += speed;
    if(frame >= frames.size() && loop) {
        frame -= frames.size();
    }
    if(frames.size() > 0)
        sprite.setTextureRect(frames[int(frame)]);
}

void Animation::setPosition(float x, float y) {
    sprite.setPosition(x, y);

}

void Animation::setSpriteTexture(sf::Texture &t) {
    sprite.setTexture(t);
}

void Animation::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}