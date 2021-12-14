//
// Created by samuel on 12/11/21.
//

#include "Enemy.h"

Enemy::Enemy(): Player("images/boss.png", 120, 120, 0, 60), HP(10) {
    name = "enemy";
    sprite.scale(1.5, 1.5);
    coords.first = windowWidth - spriteWidth;
    coords.second = windowHeight / 2;
}

void Enemy::update() {
    angle = std::atan2(playerCoords.second - coords.second, playerCoords.first - coords.first) * 180 / M_PI;
    checkBorderCoordinates();
    updateAnimation();
}

bool Enemy::changeDirection() {
    bool changed = false;
    stop = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration<double>(stop - start);
    if(time.count() > rand() % 3 + 1) { // Time required to pass before changing direction
        changed = true;
        start = std::chrono::high_resolution_clock::now(); // Reset timer
        coordsDelta.first = (rand() % 3 - 1) * (rand() % 3 + 1);
        coordsDelta.second = (rand() % 3 - 1) * (rand() % 3 + 1);
    }
    // Updating coordinates
    coords.first += coordsDelta.first;
    coords.second += coordsDelta.second;
    return changed;
}

void Enemy::updateAnimation() {
    animationStop = std::chrono::high_resolution_clock::now();
    animationTime = std::chrono::duration<double>(stop - start);
    if(animationTime.count() > 0.05) {
        texture.loadFromFile("images/boss.png");
        sprite.setTexture(texture);
    }
}

void Enemy::damageAnimation() {
    animationStart = std::chrono::high_resolution_clock::now();
    texture.loadFromFile("images/boss_damaged.png");
    sprite.setTexture(texture);
}

void Enemy::attack(std::vector<std::unique_ptr<Object>> &objects) {
    objects.push_back(std::make_unique<Projectile> (GetPosition().first, GetPosition().second,GetAngle(),10, 6.0));
    objects.back()->setName("enemy_projectile");
    objects.push_back(std::make_unique<Projectile> (GetPosition().first, GetPosition().second,GetAngle() + 20,10, 6.0));
    objects.back()->setName("enemy_projectile");
    objects.push_back(std::make_unique<Projectile> (GetPosition().first, GetPosition().second,GetAngle() - 20,10, 6.0));
    objects.back()->setName("enemy_projectile");
}

void Enemy::GetPlayerCoordinates(float x, float y) {
    playerCoords.first = x;
    playerCoords.second = y;
}

bool Enemy::checkCollision(std::unique_ptr<Object> &object) {
    float x2 = pow(coords.first - object->GetPosition().first, 2);
    float y2 = pow(coords.second - object->GetPosition().second, 2);
    float r2 = pow(radius + object->GetRadius(), 2);
    if(x2 + y2 < r2 && object->GetName() == "projectile") {
        if(HP > 0)
            HP--;
        object->kill();
        damageAnimation();
        return true;
    }
    return false;
}

const unsigned int Enemy::GetHP() const {
    return HP;
}

