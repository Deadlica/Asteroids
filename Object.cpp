//
// Created by samuel on 12/6/21.
//

#include "Object.h"

unsigned int Object::windowWidth = 0;
unsigned int Object::windowHeight = 0;

Object::Object(float x, float y, float angle, float radius):
coords({x, y}), angle(angle), radius(radius), life(true) {}

bool Object::checkCollision(std::unique_ptr<Object> &object) {
    float x2 = pow(coords.first - object->coords.first, 2);
    float y2 = pow(coords.second - object->coords.second, 2);
    float r2 = pow(radius + object->radius, 2);
    return x2 + y2 < r2;
}

void Object::draw(sf::RenderWindow &window) {
    sprite.setPosition(coords.first, coords.second);
    sprite.setRotation(angle + 90);
    window.draw(sprite);
}

void Object::setName(std::string name) {
    this->name = name;
}


void Object::setBorder(const unsigned int width, const unsigned int height) {
    windowWidth = width;
    windowHeight = height;
}

void Object::setPosition(const float x, const float y) {
    coords.first = x;
    coords.second = y;
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

const float Object::GetRadius() const {
    return radius;
}

bool Object::Alive() {
    return life;
}

void Object::kill() {
    life = false;
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