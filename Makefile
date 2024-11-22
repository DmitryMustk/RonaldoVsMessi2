BIN_NAME    = raytest
SRC_DIR     = src
BIN_DIR     = bin
INCLUDE_DIR = raylib/include
LIB_DIR     = raylib/lib

CC = clang
CFLAGS = -Wall -Wextra -Werror=implicit-function-declaration -Wpedantic -O2 -g
LDFLAGS = $(LIB_DIR)/libraylib.a -lm -lpthread -ldl -lGL -lX11

INCLUDE_PATHS = -I$(INCLUDE_DIR)

SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))

all: $(BIN_DIR)/$(BIN_NAME)

build: $(BIN_DIR)/$(BIN_NAME)

$(BIN_DIR)/$(BIN_NAME): $(OBJ_FILES)
	@echo "Linking | $@"
	@mkdir -p $(BIN_DIR)
	@$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@
	@rm -f $(OBJ_FILES)  

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling | $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	@rm -rf $(BIN_DIR)

run: all
	@echo "Running $(BIN_NAME)" ; echo
	@./$(BIN_DIR)/$(BIN_NAME)

