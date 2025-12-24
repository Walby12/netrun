CC = clang++
CFLAGS = -Isrc/include -Wall -Wextra -O3
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

netrun: src/main.cpp src/glad.c
	$(CC) $(CFLAGS) src/main.cpp src/glad.c -o netrun $(LIBS)
