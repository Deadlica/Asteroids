#include <iostream>
#include "Game.h"

int main() {
    srand((unsigned) time(0));

    //Game wrapper
    Game asteroids(1900, 1000);

    //Game loop
    while(asteroids.running()) {

        //Update
        asteroids.update();

        //Render
        asteroids.render();
    }

    return 0;
}
