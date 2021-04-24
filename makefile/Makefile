all: snake

snake: main.o game.o location.o map.o snake.o utils.o
	g++ -std=c++11 ../bin/main.o ../bin/game.o ../bin/location.o ../bin/map.o ../bin/snake.o ../bin/getch.o -pthread  -o ../bin/snake
main.o: ../src/main.cpp
	g++ -std=c++11 -c ../src/main.cpp -o ../bin/main.o
game.o: ../src/game.cpp
	g++ -std=c++11 -c ../src/game.cpp -o ../bin/game.o
location.o: ../src/location.cpp
	g++ -std=c++11 -c ../src/location.cpp -o ../bin/location.o
map.o: ../src/map.cpp
	g++ -std=c++11 -c ../src/map.cpp -o ../bin/map.o
snake.o: ../src/snake.cpp
	g++ -std=c++11 -c ../src/snake.cpp -o ../bin/snake.o
utils.o: ../src/getch.cpp
	g++ -std=c++11 -c ../src/getch.cpp -o ../bin/getch.o

open: all
	../bin/snake
