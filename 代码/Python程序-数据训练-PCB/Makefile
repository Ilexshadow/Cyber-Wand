# Makefile for NNoM project

# Compiler settings
CC = gcc

CFLAGS = -Wall -I./nnom/inc -I./nnom/inc/Layers -I./nnom/port

SRC_DIR =./nnom/src
INC_DIR =./nnom/inc
TARGET = auto_test.exe

# Source files
SOURCES = ./auto_test.c ./nnom/src/backends/* ./nnom/src/core/* ./nnom/src/layers/*
# Object files
OBJECTS = $(SOURCES:.c=.o)

# Main target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule for compiling .c files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean