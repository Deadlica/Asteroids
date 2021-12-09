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
#include <ctime>
#include <cmath>

class Object {
public:
    Object(float x, float y, float angle, float radius);

    virtual void setBorder(const unsigned int width, const unsigned int height);
    virtual void update() = 0;
    virtual int& GetCount() const = 0;
    void draw(sf::RenderWindow &window);

    sf::Sprite& GetSprite();
    sf::Texture& GetTexture();
    const std::string GetName() const;
    const std::pair<float, float> GetPosition() const;
    const float GetAngle() const;
    const float GetRadius() const;

    bool& Alive();

protected:
    void checkBorderCoordinates();
    sf::Texture texture;
    sf::Sprite sprite;
    //Coordinates, offset coordinates
    std::pair<float, float> coords, coordsDelta;
    float radius, angle, spriteWidth, spriteHeight;
    bool life;
    std::string name;
    unsigned int windowWidth, windowHeight;
private:

};


#endif //SFML_GAME_OBJECT_H
