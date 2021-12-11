program: main.cpp Game.cpp Player.cpp Object.cpp Asteroid.cpp Projectile.cpp Menu.cpp Enemy.cpp
	g++ -o main main.cpp Game.cpp Player.cpp Object.cpp Asteroid.cpp Projectile.cpp Menu.cpp Player.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: program
	./main
