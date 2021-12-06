//
// Created by samuel on 12/5/21.
//

#include "Game.h"

Game::Game(const unsigned int width, const unsigned int height):
window(sf::VideoMode(width, height), "Asteroids", sf::Style::Titlebar | sf::Style::Close),
windowWidth(width), windowHeight(height){
    window.setFramerateLimit(60);
    gameMusic.openFromFile(Arcade_Bit_Rush);
    gameMusic.play();
    spaceship.setBorder(width, height);
    initTextures();
    initSprites();
}

const bool Game::running() const {
    return window.isOpen();
}

void Game::pollEvents() {
    while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                gameMusic.stop();
                window.close();
            }
    }
}

void Game::update() {
    pollEvents();
    updatePlayerPosition();
    spaceship.updateCoordinates(Player::DOWN);

    for(int i = 0; i < 10; i++) {
        asteroids[i]->update();

        if(!asteroids[i]->Alive()) {
            asteroids[i].reset(nullptr);
        }
    }
}

void Game::render() {
    window.clear();

    window.draw(sBackground);
    window.draw(spaceship.GetSprite());
    for(int i = 0; i < 10; i++) {
        window.draw(asteroids[i]->GetSprite());
    }
    window.display();
}

void Game::generateAsteroids() {
    /*asteroids = std::unique_ptr<Asteroid[]>(new Asteroid[10]);
    for(int i = 0; i < 10; i++) {
        asteroids[i].settings(rand() % windowWidth, rand() % windowHeight, rand() % 360, 25);
    }*/
    for(int i = 0; i < 10; i++) {
        asteroids[i] = std::unique_ptr<Asteroid>(new Asteroid);
        asteroids[i]->settings(rand() % windowWidth, rand() % windowHeight, rand() % 360, 25);
    }
}

void Game::updatePlayerPosition() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        spaceship.updateCoordinates(Player::UP);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        spaceship.updateCoordinates(Player::RIGHT);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        spaceship.updateCoordinates(Player::LEFT);
}

void Game::initTextures() {
    tBackground.loadFromFile("images/space.jpg");
}

void Game::initSprites() {
    sBackground.setTexture(tBackground);
}
