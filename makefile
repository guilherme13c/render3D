CC := clang++
CFLAGS := -std=c++17 -O3 -Wall `pkg-config --libs --cflags sdl2`

INC_DIR := inc
BIN_DIR := bin
SRC_DIR := src

INC := $(INC_DIR)/config.h $(INC_DIR)/init.h $(INC_DIR)/structs.h
SRC := $(SRC_DIR)/config.cc $(SRC_DIR)/init.cc $(SRC_DIR)/main.cc
TARGET := $(BIN_DIR)/render3D

depend:
	sudo apt-get install libsdl2-dev

build: $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) -I$(INC_DIR) -g -Wno-unused-but-set-variable

clean:
	rm $(TARGET) -f
