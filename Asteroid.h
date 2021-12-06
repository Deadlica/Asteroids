//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_ASTEROID_H
#define SFML_GAME_ASTEROID_H

#include "Object.h"
#include <ctime>

class Asteroid : public Object {
public:
    Asteroid();

    void update() override;

    void setBorder(const unsigned int width, const unsigned int height);

private:
    void checkBorder();
    unsigned int windowWidth, windowHeight;
};


#endif //SFML_GAME_ASTEROID_H
