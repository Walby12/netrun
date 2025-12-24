all: main

main: src/*.c src/*.h
	cc -o netrun -O2 -Wall -Wextra src/*.c
