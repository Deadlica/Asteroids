program: main.cpp Game.cpp Player.cpp Object.cpp Asteroid.cpp Projectile.cpp Menu.cpp Enemy.cpp Animation.cpp
	g++ -O3 -o main main.cpp Game.cpp Player.cpp Object.cpp Asteroid.cpp Projectile.cpp Menu.cpp Enemy.cpp Animation.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g

run: program
	./main

install:
	sudo apt-get install libsfml-dev
