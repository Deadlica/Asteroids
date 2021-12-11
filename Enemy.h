//
// Created by samuel on 12/11/21.
//

#ifndef SFML_GAME_ENEMY_H
#define SFML_GAME_ENEMY_H

#include "Player.h"

class Enemy: public Player {
public:
    Enemy();

    void update() override;

    void GetPlayerCoordinates(float x, float y);

private:
    std::pair<float, float> playerCoords;
};


#endif //SFML_GAME_ENEMY_H
