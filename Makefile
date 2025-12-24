CLAFGS = -Wall -Wextra -O2 -Isrc/include
TARGET = netrun
SRC = src/*.c

all: $(TARGET)

setup:
	mkdir bin

clean:
	rm -rf bin/

$(TARGET): $(SRC)
	cc -o bin/$(TARGET) $(SRC) $(CLAFGS)
