# Compiler
CC = gcc

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = lib
TESTDIR = tests

# Compiler flags
CFLAGS = -Wall -Wextra -I$(INCDIR)

# Test files
TESTS := $(wildcard $(TESTDIR)/**/*.c) $(wildcard $(TESTDIR)/*.c)
# Header files
HDRS := $(wildcard $(INCDIR)/**/*.h) $(wildcard $(INCDIR)/*.h)
# Source files
SRCS := $(shell find $(SRCDIR) -type f -name '*.c')
# Object files
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Library name
LIB_NAME = libsimpengine.a

# Targets
TARGET = my_program

# Default target
all: $(LIBDIR)/$(LIB_NAME)

# Compile .c files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library target
$(LIBDIR)/$(LIB_NAME): $(OBJS)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

# Compile main program with static library
$(TARGET): main.c $(LIBDIR)/$(LIB_NAME)
	$(CC) $(CFLAGS) -L$(LIBDIR) -lsimpengine main.c -o $(TARGET) -lm -lpthread -ldl -lrt -lraylib

# Run target
run: $(TARGET)
	./$(TARGET)

# Valgrind target
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Clean target
clean:
	rm -rf $(OBJDIR) $(TARGET) $(LIBDIR)/$(LIB_NAME)

.PHONY: all clean run valgrind
