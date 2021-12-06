//
// Created by samuel on 12/6/21.
//

#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, float angle, float radius): Object(x, y, angle, radius) {
    texture.loadFromFile("images/asteroid.png");
    sprite.setTexture(texture);
    spriteWidth = texture.getSize().x;
    spriteHeight = texture.getSize().y;
    sprite.setOrigin(spriteWidth / 2, spriteHeight / 2);
    name = "asteroid";
    coordsDelta.first = (rand() % 8 - 4) + 1;
    coordsDelta.second = (rand() % 8 - 4) + 1;
}

void Asteroid::update() {
    coords.first += coordsDelta.first;
    coords.second += coordsDelta.second;
    checkBorderCoordinates();
}