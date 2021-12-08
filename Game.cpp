//
// Created by samuel on 12/5/21.
//

#include "Game.h"

Game::Game(const unsigned int width, const unsigned int height):
window(sf::VideoMode(width, height), "Asteroids", sf::Style::Titlebar | sf::Style::Close) {
    window.setFramerateLimit(60);
    centerWindowPosition();
    gameMusic.openFromFile(cigg_pk);
    gameMusic.play();
    gameMusic.setLoop(true);
    spaceship.setBorder(width, height);
    initTextures();
    initSprites();
    asteroids.resize(30);
    generateAsteroids();
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
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Space) {
                    generateProjectile();
                }
            }
    }
}

void Game::update() {
    pollEvents();
    updatePlayerPosition();
    spaceship.checkMove(Player::DOWN);
    updateAsteroids();
    updateProjectiles();
}

void Game::render() {
    window.clear();

    window.draw(sBackground);
    window.draw(spaceship.GetSprite());
    drawAsteroids();
    drawProjectiles();
    window.display();
}

void Game::centerWindowPosition() {
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5,
                                            sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));
}

void Game::generateAsteroids() {
    auto generator = [this]() {
        return std::make_unique<Asteroid> (rand() % window.getSize().x,
                                           rand() % window.getSize().y,
                                           rand() % 360, 25);
    };
    std::generate(asteroids.begin(), asteroids.end(), generator);
    auto setBorder = [this](std::vector<std::unique_ptr<Asteroid>>::value_type &a) {return a->setBorder(window.getSize().x, window.getSize().y);};
    std::for_each(asteroids.begin(), asteroids.end(), setBorder);
}

void Game::updateAsteroids() {
    auto updater = [](std::vector<std::unique_ptr<Asteroid>>::value_type &a) {
        a->update();
        if(!a->Alive()) { //Issue with removing unique_ptr from vector
            a.reset(nullptr);
            std::cout << "Dead" << std::endl;
        }
    };
    std::for_each(asteroids.begin(), asteroids.end(), updater);
}

void Game::drawAsteroids() {
    auto drawer = [this](std::vector<std::unique_ptr<Asteroid>>::value_type &a) {return a->draw(window);};
    std::for_each(asteroids.begin(), asteroids.end(), drawer);
}

void Game::generateProjectile() {
    projectiles.push_back(std::make_unique<Projectile> (spaceship.GetPosition().first, spaceship.GetPosition().second,spaceship.GetAngle(),10));
    projectiles.back().get()->setBorder(window.getSize().x, window.getSize().y);
}

void Game::updateProjectiles() {
    auto updater = [this](std::vector<std::unique_ptr<Projectile>>::value_type &p)  {
        if(p.get() != nullptr) {
            p->update();
            if (!p->Alive()) {
                std::unique_ptr<Projectile> temp;
                temp = std::move(p);
                projectiles.erase(std::find(projectiles.begin(), projectiles.end(), nullptr));
            }
        }
    };
    std::for_each(projectiles.begin(), projectiles.end(), updater);
}

void Game::drawProjectiles() {
    auto drawer = [this](std::vector<std::unique_ptr<Projectile>>::value_type &p) {return p->draw(window);};
    std::for_each(projectiles.begin(), projectiles.end(), drawer);
}

void Game::updatePlayerPosition() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        spaceship.checkMove(Player::UP);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        spaceship.checkMove(Player::RIGHT);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        spaceship.checkMove(Player::LEFT);

    if(!isAnyKeyPressed()) {
        spaceship.GetTexture().loadFromFile("images/spaceship.png");
        spaceship.GetSprite().setTexture(spaceship.GetTexture());
    }
}

bool Game::isAnyKeyPressed() {
    for(int k = -1; k < sf::Keyboard::KeyCount; ++k) {
        if(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
            return true;
    }
    return false;
}

void Game::initTextures() {
    tBackground.loadFromFile("images/space.jpg");
}

void Game::initSprites() {
    sBackground.setTexture(tBackground);
}
