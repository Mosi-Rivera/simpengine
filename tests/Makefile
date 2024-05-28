# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -lcunit -lraylib -I../include

# Directories
SRCDIR = ../src
OBJDIR = ../obj

# Header files
HDRS := $(wildcard ../include/**/*.h) $(wildcard ../include/*.h)
# Source files
SRCS := $(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/*.c)
# Test source files
TEST_SRCS := $(wildcard *.c)
# Object files
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Test executable
TEST_TARGET = test_suite

# Default target
all: test

# Compile .c files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Build and run test suite
test: $(TEST_TARGET)

# Link object files to test executable
$(TEST_TARGET): $(OBJS) $(TEST_SRCS)
	$(CC) $(CFLAGS) $(filter-out $(OBJDIR)/main.o, $^) -o $@

# Clean target
clean:
	rm -rf $(OBJDIR) $(TEST_TARGET)

.PHONY: all clean test
