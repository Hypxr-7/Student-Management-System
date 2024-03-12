# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -g -std=c++20

# Source files
SRCS = src/main.cpp src/passwordManager.cpp src/student.cpp src/fileHandle.cpp

# Object files
OBJS = $(SRCS:.c=.o)

# Executable
TARGET = myprogram

# Default target
all: $(TARGET)
	./$(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)