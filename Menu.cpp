//
// Created by samuel on 12/9/21.
//

#include "Menu.h"

Menu::Menu(const unsigned int width, const unsigned int height): windowWidth(width), windowHeight(height), position(PLAY), difficulty(ASTEROIDS) {
    initSounds();
    textFont.loadFromFile("fonts/Symtext.ttf");
    tBackground.loadFromFile("images/space.jpg");
    sBackground.setTexture(tBackground);
    sBackground.scale(windowWidth / 1920.0, windowHeight / 1200.0);

    // Setup menu buttons
    createButtons();

    showMainMenu();

    buttons[0].first.setOutlineColor(sf::Color::Transparent);
}

void Menu::run(sf::RenderWindow &window) {
    theme.play();
    sf::Event event;
    while(window.isOpen()) {
        buttons[0].first.setOutlineColor(sf::Color::Transparent);
        //buttons[0].second.setFillColor(sf::Color::White);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if(position == ASTEROIDS || position == BOSS || position == BACK)
                        showMainMenu();
                    else
                        window.close();
                }
                if (event.key.code == sf::Keyboard::Up) {
                    up();
                    break;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    down();
                    break;
                }
                if (event.key.code == sf::Keyboard::Return) {
                    enter.play();
                    if(GetPosition() == PLAY) {
                        theme.stop();
                        return;
                    }
                    else if(GetPosition() == GAMEMODE) {
                        buttons[position].second.setFillColor(sf::Color::White);
                        showSubMenu(window);
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
                    else if(GetPosition() == SUBMIT) {
                        submitScore();
                        showMainMenu();
                        topScores.clear();
                    }
                    else if(GetPosition() == BACK) {
                        showMainMenu();
                        topScores.clear();
                    }
                }
            }
        }
        window.clear();
        draw(window);
        window.display();
    }
}

void Menu::displayWin(sf::RenderWindow &window) {
    hideButtons();
    position = BACK;
    buttons[WIN].first.setOutlineColor(sf::Color::Transparent);
    buttons[WIN].second.setFillColor(sf::Color::White);
    buttons[position].first.setOutlineColor(sf::Color(54, 173, 207 ,100));
    buttons[position].second.setFillColor(sf::Color::Cyan);
}

void Menu::displayLoss(sf::RenderWindow &window, unsigned int score) {
    this->score = score;
    hideButtons();
    if(difficulty == ASTEROIDS) {
        position = SUBMIT;
        buttons[BACK].first.setOutlineColor(sf::Color(54, 173, 207 ,100));
        buttons[BACK].second.setFillColor(sf::Color::White);
    }
    else
        position = BACK;
    buttons[LOSE].first.setOutlineColor(sf::Color::Transparent);
    buttons[LOSE].second.setFillColor(sf::Color::White);
    buttons[position].first.setOutlineColor(sf::Color(54, 173, 207, 100));
    buttons[position].second.setFillColor(sf::Color::Cyan);
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(sBackground);
    for(auto e: buttons) {
        window.draw(e.first);
        window.draw(e.second);
    }
}

void Menu::up() {
    if(position != PLAY && position != ASTEROIDS && (position != SUBMIT && difficulty == ASTEROIDS)) {
        hover.play();
        buttons[position].second.setFillColor(sf::Color::White);
        buttons[--position].second.setFillColor(sf::Color::Cyan);
    }
}

void Menu::down() {
    if(position != QUIT && position != BOSS && position != BACK) {
        hover.play();
        buttons[position].second.setFillColor(sf::Color::White);
        buttons[++position].second.setFillColor(sf::Color::Cyan);
    }
}

void Menu::hideButtons() {
    for(int i = 0; i < buttons.size(); i++) {
        buttons[i].first.setOutlineColor(sf::Color::Transparent);
        buttons[i].second.setFillColor(sf::Color::Transparent);
    }
}

void Menu::showMainMenu() {
    hideButtons();
    for(int i = 0; i < 4; i++) {
            buttons[i].first.setOutlineColor(sf::Color(54, 173, 207 ,100));
            buttons[i].second.setFillColor(sf::Color::White);
    }
    position = PLAY;
    buttons[position].second.setFillColor(sf::Color::Cyan);
}

void Menu::showSubMenu(sf::RenderWindow &window) {
    hideButtons();
    buttons[0].second.setFillColor(sf::Color::Transparent);
    for(int i = 4; i < 6; i++) {
        buttons[i].first.setOutlineColor(sf::Color(54, 173, 207 ,100));
        buttons[i].second.setFillColor(sf::Color::White);
    }
    position = difficulty;
    buttons[position].second.setFillColor(sf::Color::Cyan);

}

void Menu::submitScore() {
    std::ofstream file("highscores.txt", std::ios_base::app);
    if(file.is_open()) {
        file << score << std::endl;
    }
}

const int Menu::GetPosition() const {
    return position;
}

const unsigned int Menu::GetDifficulty() const {
    return difficulty;
}

void Menu::createButtons() {
    initButton("Asteroids", windowWidth / 2, 50);
    initButton("Play", windowWidth / 2, windowHeight / 2 - 150);
    initButton("Gamemode", windowWidth / 2, windowHeight / 2);
    initButton("Quit", windowWidth / 2, windowHeight / 2 + 150);
    initButton("Asteroids", windowWidth / 2, windowHeight / 2 - 75);
    initButton("Boss", windowWidth / 2, windowHeight / 2 + 75);
    initButton("You Win!!", windowWidth / 2, windowHeight / 2 - 250);
    initButton("GAME OVER", windowWidth / 2, windowHeight / 2 - 250);
    initButton("Submit", windowWidth / 2, windowHeight / 2 - 125);
    initButton("Back", windowWidth / 2, windowHeight / 2);
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