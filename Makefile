## Compiler
CC=g++

## Compiler arguments
CARGS=-I include ./include -std=c++11 -c

all: termbot

termbot: Bot.o Laboratory.o main.o Point.o RuntimeEnvironment.o Tile.o
	$(CC) main.o Bot.o Laboratory.o Point.o RuntimeEnvironment.o Tile.o -o termbot
	
main.o:
	$(CC) $(CARGS) src/main.cpp -o main.o

Bot.o:
	$(CC) $(CARGS) src/Bot.cpp -o Bot.o

Laboratory.o:
	$(CC) $(CARGS) src/Laboratory.cpp -o Laboratory.o

Point.o:
	$(CC) $(CARGS) src/Point.cpp -o Point.o

RuntimeEnvironment.o:
	$(CC) $(CARGS) src/RuntimeEnvironment.cpp -o RuntimeEnvironment.o
	
Tile.o:
	$(CC) $(CARGS) src/Tile.cpp -o Tile.o
	
clean:
	rm *.o termbot