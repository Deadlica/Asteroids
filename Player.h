//
// Created by samuel on 12/5/21.
//

#ifndef SFML_GAME_PLAYER_H
#define SFML_GAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Player {
public:
    Player();
    enum Movement {UP, DOWN, LEFT, RIGHT};

    sf::Sprite& GetSprite();

    void setBorder(const unsigned int width, const unsigned int height);
    void checkBorderCoordinates();
    void updateCoordinates(Player::Movement move);

private:
    void updateOffset();
    void updateSpeed();

    //Player object
    sf::Texture tSpaceship;
    sf::Sprite sSpaceship;

    //Player  movement
    bool accelerate;
    static constexpr float DTR = 0.0174532925;
    float rotation;
    int maxSpeed;
    float speed;

    //Coordinates
    unsigned int windowWidth, windowHeight; //The windows border
    std::pair<float, float> coords;
    std::pair<float, float> deltaCoords;

};


#endif //SFML_GAME_PLAYER_H
