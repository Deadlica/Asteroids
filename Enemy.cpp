//
// Created by samuel on 12/11/21.
//

#include "Enemy.h"

Enemy::Enemy(): Player(450, 450) {
    name = "enemy";
    sprite.setTexture(texture);
}

void Enemy::update() {
    angle = std::atan2(playerCoords.second - coords.second, playerCoords.first - coords.first) * 180 / M_PI;
    std::cout << angle << std::endl;
}

void Enemy::GetPlayerCoordinates(float x, float y) {
    playerCoords.first = x;
    playerCoords.second = y;
}

