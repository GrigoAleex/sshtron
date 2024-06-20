# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -I src
TARGET = build/sshtron
SRCS = main.c src/connection.c src/cli.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link target from object files
$(TARGET): $(OBJS) | build
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Ensure build directory exists
build:
	mkdir -p build

# Clean build artifacts
clean:
	rm -rf build *.o src/*.o
