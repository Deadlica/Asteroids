//
// Created by samuel on 12/6/21.
//

#include "Projectile.h"

int Projectile::count = 0;

Projectile::Projectile(float x, float y, float angle, float radius, float speed): Object(x, y, angle, radius), speed(speed) {
    count++;
    texture.loadFromFile("images/laser_beam.png");
    sprite.setTexture(texture);
    spriteWidth = texture.getSize().x;
    spriteHeight = texture.getSize().y;
    sprite.setOrigin(spriteWidth / 2, spriteHeight / 2);
    name = "projectile";
    coordsDelta = {0, 0};
}

int& Projectile::GetCount() const {
    return count;
}

void Projectile::update() {
    coordsDelta.first = std::cos(angle * DTR) * speed;
    coordsDelta.second = std::sin(angle * DTR) * speed;
    coords.first += coordsDelta.first;
    coords.second += coordsDelta.second;
    if(coords.first > windowWidth || coords.first < 0 || coords.second > windowHeight || coords.second < 0) {
        life = false;
    }
}