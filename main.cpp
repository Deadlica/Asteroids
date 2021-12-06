#include <iostream>
#include "Game.h"

int main() {
    //Game wrapper
    Game asteroids(1200, 800);

    //Game loop
    while(asteroids.running()) {

        //Update
        asteroids.update();

        //Render
        asteroids.render();
    }

    return 0;
}
