//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_PROJECTILE_H
#define SFML_GAME_PROJECTILE_H

#include "Object.h"

class Projectile : public Object {
public:
    Projectile(float x, float y, float angle, float radius);

    int& GetCount() const override;

    void update() override;

private:
    static int count;
    static constexpr float DTR = 0.0174532925;
    sf::SoundBuffer buffer;
    sf::Sound gunBlast;
};


#endif //SFML_GAME_PROJECTILE_H
