//
// Created by samuel on 12/5/21.
//

#ifndef SFML_GAME_PLAYER_H
#define SFML_GAME_PLAYER_H

#include "Object.h"

//! Object that represents the player. It inherits from Object, has an rotation angle, speed etc...
class Player : public Object {
public:
    /**
     * Default constructor
     * @param file Image file for the texture.
     * @param x x-coordinate position.
     * @param y y-coordinate position.
     * @param angle Players starting rotation.
     * @param radius Players radius
     */
    Player(std::string file, float x = 0, float y = 0, float angle = 0, float radius = 20);

    /**
     * Players keyboard input for movement
     */
    enum Movement {UP, DOWN, LEFT, RIGHT};

    /**
     * Gets the amount of players that are currently alive.
     * @return Reference of the counter.
     */
    int& GetCount() const override;

    /**
     * Sets the players border for checking out of bounds in regards to the window, as well as settings the players starting position.
     * @param width RenderWindow's width.
     * @param height RenderWindow's height.
     */
    void setBorder(const unsigned int width, const unsigned int height) override;

    /**
     * Sets the texture for the player sprite.
     * @param t The texture of the player.
     */
    void setTexture(std::string t);

    /**
     * Updates the players movement depending on what keyboard input was received.
     * @param move Keyboard input.
     */
    void checkMove(Player::Movement move);

protected:
    static constexpr float DTR = 0.0174532925;
    sf::Texture texture;

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
