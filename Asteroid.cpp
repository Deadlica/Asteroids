//
// Created by samuel on 12/6/21.
//

#include "Asteroid.h"

Asteroid::Asteroid() {
    texture.loadFromFile("images/asteroid.png");
    sprite.setTexture(texture);
    name = "asteroid";
    coordsDelta.first = rand() % 8 - 4;
    coordsDelta.second = rand() % 8 - 4;
}

void Asteroid::update() {
    coords.first += coordsDelta.first;
    coords.second += coordsDelta.second;
    checkBorder();
}

void Asteroid::setBorder(const unsigned int width, const unsigned int height) {
    windowWidth = width;
    windowHeight = height;
}

void Asteroid::checkBorder() {
    if(coords.first > windowWidth)
        coords.first = 0;
    if(coords.first < 0)
        coords.first = windowWidth;

    if(coords.second > windowHeight)
        coords.second = 0;
    if(coords.second < 0)
        coords.second = windowHeight;
}