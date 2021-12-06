//
// Created by samuel on 12/6/21.
//

#include "Object.h"

int Object::count = 0;

Object::Object(): life(true) {
    count++;
}

void Object::settings(int x, int y, float angle, int radius) {
    coords.first = x;
    coords.second = y;
    this->angle = angle;
    this->radius = radius;
}

sf::Sprite& Object::GetSprite() {
    return sprite;
}

const bool Object::Alive() const {
    return life;
}
