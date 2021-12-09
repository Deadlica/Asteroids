//
// Created by samuel on 12/6/21.
//

#include "Projectile.h"

int Projectile::count = 0;

Projectile::Projectile(float x, float y, float angle, float radius) : Object(x, y, angle, radius) {
    count++;
    texture.loadFromFile("images/laser_beam.png");
    sprite.setTexture(texture);
    //buffer.loadFromFile("sounds/har_du_cigg.ogg");
    //gunBlast.setBuffer(buffer);
    //gunBlast.play();
    spriteWidth = texture.getSize().x;
    spriteHeight = texture.getSize().y;
    sprite.setOrigin(spriteWidth / 2, spriteHeight / 2);
    name = "projectile";
    coordsDelta = {0, 0};
}

int &Projectile::GetCount() const {
    return count;
}

void Projectile::update() {
    coordsDelta.first = std::cos(angle * DTR) * 12;
    coordsDelta.second = std::sin(angle * DTR) * 12;
    coords.first += coordsDelta.first;
    coords.second += coordsDelta.second;
    if(coords.first > windowWidth || coords.first < 0 || coords.second > windowHeight || coords.second < 0) {
        life = false;
    }
}