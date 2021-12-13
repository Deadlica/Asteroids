//
// Created by samuel on 12/11/21.
//

#ifndef SFML_GAME_ENEMY_H
#define SFML_GAME_ENEMY_H

#include "Player.h"
#include "Projectile.h"
#include <chrono>

class Enemy: public Player {
public:
    Enemy();

    void update() override;
    void changeDirection();

    void GetPlayerCoordinates(float x, float y);
    void detectCollision(std::unique_ptr<Object> &projectile);

private:
    std::pair<float, float> playerCoords, offset;
    unsigned int HP;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop;
    std::chrono::duration<double> time;
};


#endif //SFML_GAME_ENEMY_H
