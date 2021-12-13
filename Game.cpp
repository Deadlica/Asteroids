//
// Created by samuel on 12/5/21.
//

#include "Game.h"

Game::Game(const unsigned int width, const unsigned int height):
window(sf::VideoMode(width, height), "Asteroids", sf::Style::Titlebar | sf::Style::Close),
menu(width, height) {
    window.setFramerateLimit(60);
    centerWindowPosition();
    menu.start(window);
    spaceship = std::make_unique<Player>("images/spaceship.png");
    spaceship->setBorder(width, height);
    generateBoss();
    initTextures();
    initSprites();
    if(menu.GetDifficulty() == 4)
        generateAsteroids();
    updatePlayerPosition();
    render();
    initSounds();
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
                    //window.close();
                    clearGame();
                    menu.start(window);
                    if (menu.GetDifficulty() == 4)
                        generateAsteroids();
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
    checkObjectCollision();

    updatePlayerPosition();
    if(menu.GetDifficulty() == 5) {
        enemy->GetPlayerCoordinates(spaceship->GetPosition().first, spaceship->GetPosition().second);
        enemy->update();
        for(auto &e: objects) {
                if(e->GetName() == "projectile") {
                    enemy->detectCollision(e);
                }
        }
    }
    spaceship->checkMove(Player::DOWN);
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

void Game::checkObjectCollision() {
        auto comparer = [this](std::vector<std::unique_ptr<Object>>::value_type &p) {
            for (auto &a: objects) {
                if (p->GetName() == "projectile" && a->GetName() == "asteroid") {
                    if (p->checkCollision(a)) {
                        p->kill();
                        a->kill();
                        asteroidDeath.play();
                        points += 10;
                        score.setString("SCORE: " + std::to_string(points));
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
                spaceship->kill();
                clearGame();
                menu.start(window);
                gameMusic.play();
                score.setString("SCORE: " + std::to_string(points));
                if(menu.GetDifficulty() == 4)
                    generateAsteroids();
                return;
            }
        }
    }
}

void Game::clearGame() {
    gameMusic.stop();
    while(objects.size() != 0) {objects.pop_back();}
    objects.resize(0);
    Asteroid::count = 0;
    Projectile::count = 0;
    points = 0;
}

void Game::generateAsteroids() {
    while(Asteroid::count < 15) {
        objects.push_back(std::make_unique<Asteroid> (rand() % window.getSize().x,rand() % window.getSize().y,rand() % 360, 25));
        objects.back().get()->setBorder(window.getSize().x, window.getSize().y);
    }
}

void Game::generateProjectile() {
    objects.push_back(std::make_unique<Projectile> (spaceship->GetPosition().first, spaceship->GetPosition().second,spaceship->GetAngle(),10));
    objects.back().get()->setBorder(window.getSize().x, window.getSize().y);
}

void Game::generateBoss() {
    enemy = std::make_unique<Enemy>();
    enemy->setBorder(window.getSize().x, window.getSize().y);
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
    if(menu.GetDifficulty() == 5)
        enemy->draw(window);

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
    textFont.loadFromFile("fonts/Symtext.ttf");
    score.setString("Score: " + std::to_string(points));
    score.setFont(textFont);
    score.setCharacterSize(50);
    score.setPosition(0, -10);
    score.setFillColor(sf::Color::Cyan);
}

void Game::initSprites() {
    sBackground.setTexture(tBackground);
}

void Game::initSounds() {
    gameMusic.openFromFile(Arcade_Bit_Rush);
    gameMusic.play();
    gameMusic.setLoop(true);
    buffer.loadFromFile("sounds/ja_brorsan.ogg");
    asteroidDeath.setBuffer(buffer);
    buffer2.loadFromFile("sounds/Laser Gun.ogg");
    projectileFired.setBuffer(buffer2);
}
