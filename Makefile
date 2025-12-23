all: main

main:
	gcc src/main.c -o netrun -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -O3 
