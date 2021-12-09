//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_ASTEROID_H
#define SFML_GAME_ASTEROID_H

#include "Object.h"

class Asteroid : public Object {
public:
    Asteroid(float x, float y, float angle, float radius);

    int& GetCount() const override;

    void update() override;
    static int count;
private:


};


#endif //SFML_GAME_ASTEROID_H
