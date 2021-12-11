//
// Created by samuel on 12/5/21.
//

#ifndef SFML_GAME_PLAYER_H
#define SFML_GAME_PLAYER_H

#include "Object.h"
#include <iostream>

class Player : public Object {
public:
    Player(float x = 0, float y = 0, float angle = 0, float radius = 20);
    enum Movement {UP, DOWN, LEFT, RIGHT};

    int& GetCount() const override;

    void setBorder(const unsigned int width, const unsigned int height) override;
    void checkMove(Player::Movement move);

protected:
    static constexpr float DTR = 0.0174532925;

private:
    void update() override;
    void updateOffset();
    void updateSpeed();

    static int count;

    //Player  movement
    bool accelerate;
    int maxSpeed;
    float speed;


};


#endif //SFML_GAME_PLAYER_H
