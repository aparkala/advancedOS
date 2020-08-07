# Makefile

# all means, by typing in "make" it will run all definitions to
# the left of the : in the definitions
all : main

main: main.cpp Algorithm.cpp Fifo.cpp Lfu.cpp Lru.cpp Memory.cpp Mfu.cpp Page.cpp Process.cpp RandomPick.cpp StatsCollector.cpp
	g++ -O3 -W main.cpp Algorithm.cpp Fifo.cpp Lfu.cpp Lru.cpp Memory.cpp Mfu.cpp Page.cpp Process.cpp RandomPick.cpp StatsCollector.cpp -o main;

# More examples of other independent C files
#
# client: client.c
#       gcc -Wall client.c -o client

# checkin: checkin.c
#       gcc -Wall checkin.c -o checkin

run: main
	./main > Output/results
clean: main
	rm main
