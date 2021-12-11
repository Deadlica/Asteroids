//
// Created by samuel on 12/9/21.
//

#include "Menu.h"

Menu::Menu(const unsigned int width, const unsigned int height): windowWidth(width), windowHeight(height) {
    position = PLAY;
    difficulty = ASTEROIDS;
    initSounds();
    textFont.loadFromFile("fonts/Symtext.ttf");
    initButton("Asteroids", width / 2, 50);
    initButton("Play", width / 2, height / 2 - 150);
    initButton("Gamemode", width / 2, height / 2);
    initButton("Quit", width / 2, height / 2 + 150);
    buttons[position - 1].first.setOutlineColor(sf::Color::Transparent);
    buttons[position].second.setFillColor(sf::Color::Cyan);
}

void Menu::subMenu(sf::RenderWindow &window) {
    hideMainMenu();
    window.clear();
    initButton("Asteroids", windowWidth / 2, windowHeight / 2 - 75);
    initButton("Boss", windowWidth / 2, windowHeight / 2 + 75);
    position = difficulty;
    buttons[position].second.setFillColor(sf::Color::Cyan);

}

void Menu::start(sf::RenderWindow &window) {
    theme.play();
    sf::Event event;
    while(window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    up();
                    break;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    down();
                    break;
                }
                if (event.key.code == sf::Keyboard::Return) {
                    if(GetPosition() == PLAY) {
                        theme.stop();
                        return;
                    }
                    else if(GetPosition() == GAMEMODE) {
                        buttons[position].second.setFillColor(sf::Color::White);
                        subMenu(window);
                    }
                    else if (GetPosition() == QUIT) {
                        window.close();
                        return;
                    }
                    else if(GetPosition() == ASTEROIDS) {
                        showMainMenu();
                        difficulty = ASTEROIDS;
                    }
                    else if(GetPosition() == BOSS) {
                        showMainMenu();
                        difficulty = BOSS;
                    }
                }
            }
        }
        window.clear();
        draw(window);
        window.display();
    }
}

void Menu::stop(sf::RenderWindow &window) {

}

void Menu::draw(sf::RenderWindow &window) {
    for(auto e: buttons) {
        window.draw(e.first);
        window.draw(e.second);
    }
}

void Menu::up() {
    if(position != PLAY && position != ASTEROIDS) {
        hover.play();
        buttons[position].second.setFillColor(sf::Color::White);
        buttons[--position].second.setFillColor(sf::Color::Cyan);
    }
}

void Menu::down() {
    if(position != QUIT && position != BOSS) {
        hover.play();
        buttons[position].second.setFillColor(sf::Color::White);
        buttons[++position].second.setFillColor(sf::Color::Cyan);
    }
}

void Menu::hideMainMenu() {
    for(auto &e: buttons) {
        if(e.second.getString() != "Asteriods") {
            e.first.setOutlineColor(sf::Color::Transparent);
            e.second.setFillColor(sf::Color::Transparent);
        }
    }
}

void Menu::showMainMenu() {
    buttons.erase(buttons.begin() + 4, buttons.begin() + 6);
    for(auto &e: buttons) {
        if(e.second.getString() != "Asteriods") {
            e.first.setOutlineColor(sf::Color(54, 173, 207 ,100));
            e.second.setFillColor(sf::Color::White);
        }
    }
    position = PLAY;
    buttons[position].second.setFillColor(sf::Color::Cyan);
}

const int Menu::GetPosition() const {
    return position;
}

const unsigned int Menu::GetDifficulty() const {
    return difficulty;
}

void Menu::initButton(std::string text, const unsigned int x, const unsigned int y) {
    std::pair<sf::RectangleShape, sf::Text> temp;
    initRect(temp.first, x, y);
    initText(temp.first, temp.second, text, x, y);
    buttons.push_back(temp);
}

void Menu::initText(sf::RectangleShape rect, sf::Text &label, std::string text, const unsigned int x, unsigned int y) {
    label.setFont(textFont);
    label.setString(text);
    label.setFillColor(sf::Color::White);
    label.setCharacterSize(70);
    label.setOrigin(label.getGlobalBounds().width / 2, 45);
    label.setPosition(x, y);
}

void Menu::initRect(sf::RectangleShape &rect, const unsigned int x, const unsigned int y) {
    rect.setSize(sf::Vector2f(450, 90));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(54, 173, 207 ,100));
    rect.setOutlineThickness(10);
    rect.setOrigin(225, 45);
    rect.setPosition(x, y);
}

void Menu::initSounds() {
    theme.openFromFile("sounds/main_menu.ogg");
    theme.setLoop(true);
    buffer1.loadFromFile("sounds/hover_button.ogg");
    buffer2.loadFromFile("sounds/enter_button.ogg");
    hover.setBuffer(buffer1);
    enter.setBuffer(buffer2);
}


