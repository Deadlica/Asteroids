//
// Created by samuel on 12/5/21.
//

#include "Player.h"

Player::Player(float x, float y, float angle, float radius): Object(x, y, angle, radius), accelerate(false), maxSpeed(5), speed(0) {
    texture.loadFromFile("images/spaceship.png");
    sprite.setTexture(texture);
    sprite.setOrigin(20, 20);
    coordsDelta = {0, 0};
}

void Player::setBorder(const unsigned int width, const unsigned int height) {
    //Tells the Player object the size of the window
    Object::setBorder(width, height);
    coords.first = windowWidth / 2;
    coords.second = windowHeight / 2;
}

void Player::update() {
    updateOffset(); //Calculates the offset for the new x,y positions
    updateSpeed(); //Increases speed

    //Sets new coordinate values
    coords.first += coordsDelta.first;
    coords.second += coordsDelta.second;

    //Checks that player is not out of bounds
    checkBorderCoordinates();
    sprite.setPosition(coords.first, coords.second);
    sprite.setRotation(angle + 90);
}

void Player::checkMove(Player::Movement move) {
    //Checks which movement was inputted

    //Rotate right
    if(move == Movement::RIGHT)
        angle += 3;

    //Rotate left
    if(move == Movement::LEFT)
        angle -= 3;

    //Accelerate
    if(move == Movement::UP) {
        accelerate = true;
    }
    //Brake
    else {
        accelerate = false;
    }
    //performs the coordinate updates
    update();
}

void Player::updateOffset() {
    if(accelerate) {
        GetTexture().loadFromFile("images/spaceship_boost.png");
        GetSprite().setTexture(GetTexture());
        coordsDelta.first += std::cos(angle * DTR) * 0.1;
        coordsDelta.second += std::sin(angle * DTR) * 0.1;
    }
    else {
        coordsDelta.first *= 0.99;
        coordsDelta.second *= 0.99;
    }
}

void Player::updateSpeed() {
    speed = std::sqrt(coordsDelta.first * coordsDelta.first + coordsDelta.second * coordsDelta.second);
    if(speed > maxSpeed) {
        coordsDelta.first *= maxSpeed / speed;
        coordsDelta.second *= maxSpeed / speed;
    }
}
