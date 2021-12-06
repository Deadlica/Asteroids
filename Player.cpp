//
// Created by samuel on 12/5/21.
//

#include "Player.h"

Player::Player(): accelerate(false), rotation(0), maxSpeed(5), speed(0), coords(200, 200), deltaCoords(0, 0) {
    tSpaceship.loadFromFile("images/spaceship.png");
    sSpaceship.setTexture(tSpaceship);
    sSpaceship.setOrigin(20, 20);
}

sf::Sprite& Player::GetSprite() {
    return sSpaceship;
}

void Player::setBorder(const unsigned int width, const unsigned int height) {
    //Tells the Player object the size of the window
    windowWidth = width;
    windowHeight = height;
}

void Player::checkBorderCoordinates() {
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

void Player::updateCoordinates(Player::Movement move) {
    //Rotate right
    if(move == Movement::RIGHT)
        rotation += 3;

    //Rotate left
    if(move == Movement::LEFT)
        rotation -= 3;

    //Accelerate
    if(move == Movement::UP)
        accelerate = true;
    //Brake
    else
        accelerate = false;

    updateOffset(); //Calculates the offset for the new x,y positions
    updateSpeed(); //Increases speed

    //Sets new coordinate values
    coords.first += deltaCoords.first;
    coords.second += deltaCoords.second;

    //Checks that player is not out of bounds
    checkBorderCoordinates();

    sSpaceship.setPosition(coords.first, coords.second);
    sSpaceship.setRotation(rotation + 90);

}

void Player::updateOffset() {
    if(accelerate) {
        deltaCoords.first += std::cos(rotation * DTR) * 0.1;
        deltaCoords.second += std::sin(rotation * DTR) * 0.1;
    }
    else {
        deltaCoords.first *= 0.99;
        deltaCoords.second *= 0.99;
    }
}

void Player::updateSpeed() {
    speed = std::sqrt(deltaCoords.first * deltaCoords.first + deltaCoords.second * deltaCoords.second);
    if(speed > maxSpeed) {
        deltaCoords.first *= maxSpeed / speed;
        deltaCoords.second *= maxSpeed / speed;
    }
}
