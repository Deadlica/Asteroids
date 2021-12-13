//
// Created by samuel on 12/11/21.
//

#include "Enemy.h"

Enemy::Enemy(): Player("images/boss.png", 120, 120, 0, 60), HP(100), offset({0.0, 0.0}) {
    name = "enemy";
    sprite.scale(1.2, 1.2);
}

void Enemy::update() {
    angle = std::atan2(playerCoords.second - coords.second, playerCoords.first - coords.first) * 180 / M_PI;
    changeDirection();
    checkBorderCoordinates();
}

void Enemy::changeDirection() {
    stop = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration<double>(stop - start);
    if(time.count() > rand() % 3 + 1) { // Time required to pass before changing direction
        start = std::chrono::high_resolution_clock::now(); // Reset timer
        offset.first = (rand() % 3 - 1) * (rand() % 3 + 1);
        offset.second = (rand() % 3 - 1) * (rand() % 3 + 1);
    }
    // Updating coordinates
    coords.first += offset.first;
    coords.second += offset.second;
}

void Enemy::GetPlayerCoordinates(float x, float y) {
    playerCoords.first = x;
    playerCoords.second = y;
}

void Enemy::detectCollision(std::unique_ptr<Object> &projectile) {
    if(checkCollision(projectile)) {
        HP--;
        projectile->kill();
    }
}

