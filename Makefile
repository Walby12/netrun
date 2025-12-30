RAYLIB_PATH = raylib
INCLUDES = -I$(RAYLIB_PATH)/include
LIBRARIES = -L$(RAYLIB_PATH)/lib

CFLAGS = -Wall -Wextra -O2
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = bin/netrun.exe
SRC = src/main.c

.PHONY: all setup clean

all: setup $(TARGET)

setup:
	@if not exist bin mkdir bin

$(TARGET): $(SRC)
	gcc $(SRC) $(CFLAGS) $(INCLUDES) $(LIBRARIES) $(LIBS) -o $(TARGET)

clean:
	@if exist bin rmdir /s /q bin
