//
// Created by samuel on 12/5/21.
//

#include "Game.h"

Game::Game(const unsigned int width, const unsigned int height):
window(sf::VideoMode(width, height), "Asteroids", sf::Style::Titlebar | sf::Style::Close),
menu(width, height) {
    window.setFramerateLimit(60);
    centerWindowPosition();

    // Prompts menu
    menu.run(window);

    // Initializations
    initTextures();
    initSprites();
    initSounds();
    startGame();
}

const bool Game::running() const {
    return window.isOpen();
}

void Game::pollEvents() {
    while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) { // Exit game
                gameMusic.stop();
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) { // Exits current gamemode
                    clearGame();
                    menu.run(window);
                    startGame();
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // Fires a projectile
                    generateProjectile();
                    projectileFired.play();
                }
            }
    }
}

void Game::update() {
    pollEvents(); // Checks events

    // Collision detection
    checkObjectCollision();
    checkPlayerCollision();

    // Updates
    updatePlayer();
    updateObjects();
    updateEnemy();
    updateScore();
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
                        asteroidDeath.play();
                        p->kill();
                        a->kill();
                        points += 10;
                    }
                }
            }
        };
        std::for_each(objects.begin(), objects.end(), comparer);
}

void Game::checkPlayerCollision() {
    for(auto &o: objects) {
        if(o->GetName() == "asteroid" || o->GetName() == "enemy_projectile") {
            if(spaceship->checkCollision(o)) {
                clearGame();
                menu.displayLoss(window, points);
                menu.run(window);
                startGame();
                return;
            }
        }
    }
}

void Game::startGame() {
    // Resets score
    points = 0;

    generatePlayer();

    if(menu.GetDifficulty() == Menu::ASTEROIDS) {
        gameMusic.openFromFile(Arcade_Bit_Rush);
        generateAsteroids();
    }
    else if(menu.GetDifficulty() == Menu::BOSS) {
        gameMusic.openFromFile(Hopes_And_Dreams);
        generateBoss();
    }
    gameMusic.play();
}

void Game::clearGame() {
    gameMusic.stop();

    // Clears player
    spaceship->kill();
    auto tempSpaceship = std::move(spaceship);

    // Clears enemy
    if(menu.GetDifficulty() == Menu::BOSS) {
        enemy->kill();
        auto tempEnemy = std::move(enemy);
    }

    // Clears projectiles, asteroids
    objects.clear();
    Asteroid::count = 0;
    Projectile::count = 0;
}

void Game::generateAsteroids() {
    while(Asteroid::count < 15)
        objects.push_back(std::make_unique<Asteroid> (rand() % window.getSize().x,rand() % window.getSize().y,rand() % 360, 25));
}

void Game::generateProjectile() {
    objects.push_back(std::make_unique<Projectile> (spaceship->GetPosition().first, spaceship->GetPosition().second,spaceship->GetAngle(),10, 12.0));
}

void Game::generatePlayer() {
    spaceship = std::make_unique<Player>("images/spaceship.png");
    spaceship->setBorder(window.getSize().x, window.getSize().y);
}

void Game::generateBoss() {
    enemy = std::make_unique<Enemy>();
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

void Game::updateEnemy() {
    if(menu.GetDifficulty() == Menu::BOSS) {
        enemy->GetPlayerCoordinates(spaceship->GetPosition().first, spaceship->GetPosition().second);
        enemy->update();
        if(enemy->changeDirection())
            enemy->attack(objects);
        for(auto &p: objects) {
            enemy->checkCollision(p);
        }
        if(enemy->GetHP() == 0) {
            clearGame();
            menu.displayWin(window);
            menu.run(window);
            startGame();
        }
    }
}

void Game::updateScore() {
    if(menu.GetDifficulty() == Menu::ASTEROIDS)
        score.setString("SCORE: " + std::to_string(points));
    else if(menu.GetDifficulty() == Menu::BOSS)
        score.setString("BOSS HP: " + std::to_string(enemy->GetHP()));
}

void Game::drawObjects() {
    auto drawer = [this](std::vector<std::unique_ptr<Object>>::value_type &o) {return o->draw(window);};
    std::for_each(objects.begin(), objects.end(), drawer);
    window.draw(spaceship->GetSprite());
    if(menu.GetDifficulty() == Menu::BOSS)
        enemy->draw(window);

}

void Game::updatePlayer() {
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
    spaceship->checkMove(Player::DOWN);
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
    score.setFont(textFont);
    score.setCharacterSize(50);
    score.setPosition(0, -10);
    score.setFillColor(sf::Color::Cyan);
}

void Game::initSprites() {
    sBackground.setTexture(tBackground);
    sBackground.scale(window.getSize().x / 1920.0, window.getSize().y / 1200.0);
}

void Game::initSounds() {
    gameMusic.openFromFile(Arcade_Bit_Rush);
    gameMusic.setLoop(true);
    buffer.loadFromFile("sounds/boom4.ogg");
    asteroidDeath.setBuffer(buffer);
    buffer2.loadFromFile("sounds/Laser Gun.ogg");
    projectileFired.setBuffer(buffer2);
}
