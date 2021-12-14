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
    bool changeDirection();
    void updateAnimation();
    void damageAnimation();
    void attack(std::vector<std::unique_ptr<Object>> &objects);

    void GetPlayerCoordinates(float x, float y);
    bool checkCollision(std::unique_ptr<Object> &object) override;
    const unsigned int GetHP() const;

private:
    std::pair<float, float> playerCoords;
    unsigned int HP;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, animationStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop, animationStop;
    std::chrono::duration<double> time, animationTime;
};


#endif //SFML_GAME_ENEMY_H
