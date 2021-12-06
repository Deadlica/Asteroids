program: main.cpp Game.cpp Player.cpp Object.cpp Asteroid.cpp
	g++ -o main main.cpp Game.cpp Player.cpp Object.cpp Asteroid.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: program
	./main
