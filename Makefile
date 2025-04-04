# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Isqlite3   -ggdb -O0
JSON_C_DIR=/usr/local
# CFLAGS += -I$(JSON_C_DIR)/include/json-c
# Or to use lines like: #include <json-c/json_object.h>
CFLAGS += -I$(JSON_C_DIR)/include
LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c
LDFLAGS+= -lsqlite3
# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR= bin
INCLUDE_DIR = include

# Target executable
TARGET = program

# Find all .c files in src/ and convert them to .o files in obj/
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default rule: Build the target
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o ./bin/$(TARGET) $(LDFLAGS) 
# Compile each .c file into an .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj/ directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule to remove compiled files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
init:
	rm -rf "data" "schemes"
