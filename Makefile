CC = g++

all: main.o
	$(CC) main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system
main.o: main.cpp
	$(CC) -I src/include -c main.cpp
clean:
	rm -f *.o
	rm main

