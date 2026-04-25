CC = gcc
CFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

BUILD_DIR = build

SRC = $(SRC_DIR)/$(FILE).c
OUT = $(BUILD_DIR)/$(FILE).exe

all: $(BUILD_DIR)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

runTest: SRC_DIR = Raylib\ Test
runTest: FILE ?= assetsLoading
runTest: all
	./$(OUT)

run: SRC_DIR = Pendulum
run: FILE ?= double-pendulum
run: all
	./$(OUT)

clean:
	rm -f $(BUILD_DIR)/*.exe