//
// Created by samuel on 12/6/21.
//

#include "Asteroid.h"

int Asteroid::count = 0;

Asteroid::Asteroid(sf::Texture &t, float x, float y, float angle, float radius, std::pair<float, float> playerPosition):
Object(x, y, angle, radius), rock(64, 64, ((rand() % 5) + 2) / 10.0, 16, true) {
    count++;
    rock.setSpriteTexture(t);
    name = "asteroid";
    coordsDelta.first = (rand() % 8 - 4) + 1;
    coordsDelta.second = (rand() % 8 - 4) + 1;
    dontSpawnOnPlayer(playerPosition);
}

int& Asteroid::GetCount() const {
    return count;
}

void Asteroid::update() {
    coords.first += coordsDelta.first;
    coords.second += coordsDelta.second;
    rock.setPosition(coords.first, coords.second);
    rock.update();
    checkBorderCoordinates();
}

void Asteroid::draw(sf::RenderWindow &window) {
    rock.draw(window);
}

void Asteroid::dontSpawnOnPlayer(std::pair<float, float> &playerPosition) {
    while(pow(GetPosition().first - playerPosition.first, 2) + pow(GetPosition().second - playerPosition.second, 2) < pow(120, 2)) {
        setPosition(rand() % windowWidth, rand() % windowHeight);
    }
}