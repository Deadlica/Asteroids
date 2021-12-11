#include <iostream>
#include "Game.h"
#include "Menu.h"

int main() {
    srand((unsigned) time(0));

    //Game wrapper
    Game asteroids(1600, 900);

    //Game loop
    while(asteroids.running()) {

        //Update
        asteroids.update();

        //Render
        asteroids.render();
    }

    /*sf::RenderWindow MENU(sf::VideoMode(1600, 900), "Menu", sf::Style::Titlebar | sf::Style::Close);
    Menu mainMenu(MENU.getSize().x, MENU.getSize().y);
    sf::Texture lol;
    lol.loadFromFile("images/space.jpg");
    sf::Sprite eee;
    eee.setTexture(lol);
    MENU.draw(eee);

    mainMenu.start(MENU);*/

    return 0;
}
