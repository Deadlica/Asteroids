//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_ASTEROID_H
#define SFML_GAME_ASTEROID_H

#include "Object.h"

class Asteroid : public Object {
public:
    Asteroid(float x, float y, float angle, float radius);

    void update() override;

private:

};


#endif //SFML_GAME_ASTEROID_H
