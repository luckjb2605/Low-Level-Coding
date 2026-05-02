
CFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
BUILD_DIR = build

SRC = $(SRC_DIR)/$(FILE).$(EXT)
OUT = $(BUILD_DIR)/$(FILE).exe

all: $(BUILD_DIR)
	$(COMPILER) "$(SRC)" -o $(OUT) $(CFLAGS)

exe:
	./$(OUT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run-%:
	$(MAKE) SRC_DIR="$($*_SRC)" \
					FILE="$($*_DEFAULT)" \
					EXT="$($*_EXT)" \
					COMPILER="$($*_COMPILER)" \
	all
	$(MAKE) FILE="$($*_DEFAULT)" exe

test_SRC = Raylib Test
test_DEFAULT = assetsLoading
test_EXT = c
test_COMPILER = gcc

pendulum_SRC = Pendulum
pendulum_DEFAULT = double-pendulum
pendulum_EXT = c
pendulum_COMPILER = gcc

clean:
	rm -f $(BUILD_DIR)/*.exe