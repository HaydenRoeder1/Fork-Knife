CFLAGS = -g -Wall -Wextra -DDEBUG -std=c++14
all: game.o
	g++ $(CFLAGS) game.o weapons.o player.o enemy.o consumable.o -o game
game.o: weapons.o player.o enemy.o consumable.o game.cpp
	g++ -c $(CFLAGS) game.cpp -o game.o
weapons.o: weapons.cpp
	g++ -c $(CFLAGS) weapons.cpp -o weapons.o
consumable.o: consumable.cpp
	g++ -c $(CFLAGS) consumable.cpp -o consumable.o
player.o: player.cpp
	g++ -c $(CFLAGS) player.cpp -o player.o
enemy.o: enemy.cpp
	g++ -c $(CFLAGS) enemy.cpp -o enemy.o
clean:
	rm -rf *.o
