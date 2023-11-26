# Makefile for hello_sfml.cpp

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Executable name
TARGET = main

# Source files
SRCS = main.cpp player.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Compile rule
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Clean rule
clean:
	rm -f $(OBJS)
