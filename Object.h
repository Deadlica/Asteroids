//
// Created by samuel on 12/6/21.
//

#ifndef SFML_GAME_OBJECT_H
#define SFML_GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <utility>
#include <string>

class Object {
public:
    Object();

    void settings(int x, int y, float angle, int radius);

    virtual void update() = 0;

    sf::Sprite& GetSprite();

    const bool Alive() const;

protected:
    sf::Texture texture;
    sf::Sprite sprite;
    //Coordinates, offset coordinates
    std::pair<float, float> coords, coordsDelta;
    float radius, angle;
    bool life;
    std::string name;
private:
    static int count;
};


#endif //SFML_GAME_OBJECT_H
