//
// Created by samuel on 12/6/21.
//

#include "Object.h"

int Object::count = 0;

Object::Object(float x, float y, float angle, float radius):
coords({x, y}), angle(angle), radius(radius), life(true) {
    count++;
}

void Object::settings(int x, int y, float angle, int radius) {
    coords.first = x;
    coords.second = y;
    this->angle = angle;
    this->radius = radius;
}

void Object::setBorder(const unsigned int width, const unsigned int height) {
    windowWidth = width;
    windowHeight = height;
}

void Object::draw(sf::RenderWindow &window) {
    sprite.setPosition(coords.first, coords.second);
    sprite.setRotation(angle + 90);
    window.draw(sprite);
}

sf::Sprite& Object::GetSprite() {
    return sprite;
}

sf::Texture& Object::GetTexture() {
    return texture;
}

const std::string Object::GetName() const {
    return name;
}

const std::pair<float, float> Object::GetPosition() const {
    return coords;
}

const float Object::GetAngle() const {
    return angle;
}

const bool Object::Alive() const {
    return life;
}

void Object::checkBorderCoordinates() {
    //Checks x-axis bounds
    if(coords.first > windowWidth)
        coords.first = 0;
    if(coords.first < 0)
        coords.first = windowWidth;

    //Checks y-axis bounds
    if(coords.second > windowHeight)
        coords.second = 0;
    if(coords.second < 0)
        coords.second = windowHeight;
}
