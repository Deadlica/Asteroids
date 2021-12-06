program: main.cpp Game.cpp Player.cpp Object.cpp Asteroid.cpp Projectile.cpp
	g++ -o main main.cpp Game.cpp Player.cpp Object.cpp Asteroid.cpp Projectile.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: program
	./main
