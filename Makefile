#Copyright 2024 Sal Sicari
CC = g++
CFLAGS = -Wall -Werror -pedantic -g -std=c++17 -o3
OBJECTS = main.o AudioDecoder.o Visualizer.o
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
FFTFLAGS = -lfftw3
MPGFLAGS = -lmpg123

all: AudioVisualizer

AudioVisualizer: $(OBJECTS)
	$(CC) $(CFLAGS) -o AudioVisualizer $(OBJECTS) $(SFMLFLAGS) $(FFTFLAGS) $(MPGFLAGS)

main.o: main.cpp AudioDecoder.hpp Visualizer.hpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

AudioDecoder.o: AudioDecoder.cpp AudioDecoder.hpp
	$(CC) $(CFLAGS) -c AudioDecoder.cpp -o AudioDecoder.o

Visualizer.o: Visualizer.cpp Visualizer.hpp AudioDecoder.hpp
	$(CC) $(CFLAGS) -c Visualizer.cpp -o Visualizer.o

clean:
	rm AudioVisualizer *.o
