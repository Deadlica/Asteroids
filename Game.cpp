//
// Created by samuel on 12/5/21.
//

#include "Game.h"

Game::Game(const unsigned int width, const unsigned int height):
window(sf::VideoMode(width, height), "Asteroids", sf::Style::Titlebar | sf::Style::Close) {
    window.setFramerateLimit(60);
    centerWindowPosition();
    spaceship = std::make_unique<Player>();
    spaceship->setBorder(width, height);
    initSounds();
    initTextures();
    initSprites();
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
            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Escape) {
                    gameMusic.stop();
                    window.close();
                }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Space) {
                    generateProjectile();
                    projectileFired.play();
                }
            }
    }
}

void Game::update() {
    pollEvents();
    checkCollision();
    updatePlayerPosition();
    spaceship->checkMove(Player::DOWN);//spaceship.checkMove(Player::DOWN);
    updateObjects();
    checkPlayerCollision();

}

void Game::render() {
    window.clear();
    window.draw(sBackground);
    drawObjects();
    window.draw(score);
    window.display();
}

void Game::centerWindowPosition() {
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5,
                                            sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));
}

void Game::checkCollision() {
        auto comparer = [this](std::vector<std::unique_ptr<Object>>::value_type &p) {
            for (auto &a: objects) {
                if (p->GetName() == "projectile" && a->GetName() == "asteroid") {
                    if (isCollision(p, a)) {
                        p->Alive() = false;
                        a->Alive() = false;
                        asteroidDeath.play();
                    }
                }
            }
        };
        std::for_each(objects.begin(), objects.end(), comparer);
}

bool Game::isCollision(std::vector<std::unique_ptr<Object>>::value_type &p, std::vector<std::unique_ptr<Object>>::value_type &a) {
    float x2 = pow(p->GetPosition().first - a->GetPosition().first, 2);
    float y2 = pow(p->GetPosition().second - a->GetPosition().second, 2);
    float r2 = pow(p->GetRadius() + a->GetRadius(), 2);
    return x2 + y2 < r2;
}

void Game::checkPlayerCollision() {
    for(auto &a: objects) {
        if(a->GetName() == "asteroid") {
            if(pow(spaceship->GetPosition().first - a->GetPosition().first, 2) +
               pow(spaceship->GetPosition().second - a->GetPosition().second, 2) <
               pow(spaceship->GetRadius() + a->GetRadius(), 2)) {
                a->Alive() = false;
                asteroidDeath.play();
                spaceship->GetSprite().scale(0.0001, 0.0001); //FIX THIS
                break;
            }
        }
    }
}

void Game::generateAsteroids() {
    while(Asteroid::count < 30) {
        objects.push_back(std::make_unique<Asteroid> (rand() % window.getSize().x,rand() % window.getSize().y,rand() % 360, 25));
        objects.back().get()->setBorder(window.getSize().x, window.getSize().y);
    }
}

void Game::generateProjectile() {
    objects.push_back(std::make_unique<Projectile> (spaceship->GetPosition().first, spaceship->GetPosition().second,spaceship->GetAngle(),10));
    objects.back().get()->setBorder(window.getSize().x, window.getSize().y);
}

void Game::updateObjects() {
    auto updater = [this](std::vector<std::unique_ptr<Object>>::value_type &o) {
        if(o.get() != nullptr) {
            o->update();
            if (!o->Alive()) {
                o->GetCount() -= 1;
                if(o->GetName() == "asteroid")
                    generateAsteroids();
                auto temp = std::move(o);
                objects.erase(std::find(objects.begin(), objects.end(), nullptr));
            }
        }
    };
    std::for_each(objects.begin(), objects.end(), updater);
}

void Game::drawObjects() {
    auto drawer = [this](std::vector<std::unique_ptr<Object>>::value_type &o) {return o->draw(window);};
    std::for_each(objects.begin(), objects.end(), drawer);
    if(spaceship != nullptr)
        window.draw(spaceship->GetSprite());

}

void Game::updatePlayerPosition() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        spaceship->checkMove(Player::UP);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        spaceship->checkMove(Player::RIGHT);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        spaceship->checkMove(Player::LEFT);

    if(!isAnyKeyPressed()) {
        spaceship->GetTexture().loadFromFile("images/spaceship.png");
        spaceship->GetSprite().setTexture(spaceship->GetTexture());
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
    score.setString("Score: 10");
    score.setPosition(-24, -24);
    score.setCharacterSize(24);
    score.setColor(sf::Color::Red);
}

void Game::initSprites() {
    sBackground.setTexture(tBackground);
}

void Game::initSounds() {
    gameMusic.openFromFile(cigg_pk);
    gameMusic.play();
    gameMusic.setLoop(true);
    buffer.loadFromFile("sounds/ja_brorsan.ogg");
    asteroidDeath.setBuffer(buffer);
    buffer2.loadFromFile("sounds/har_du_cigg.ogg");
    projectileFired.setBuffer(buffer2);
}
