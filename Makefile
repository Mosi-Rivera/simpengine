# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -lraylib -lm -lpthread -ldl -lrt -I$(INCDIR)

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
TESTDIR = tests

#Test files
TESTS := $(wildcard $(TESTDIR)/**/*.c) $(wildcard $(TESTDIR)/*.c)
#Header files
HDRS := $(wildcard $(INCDIR)/**/*.h) $(wildcard $(INCDIR)/*.h)
# Source files
SRCS := $(shell find $(SRCDIR) -type f -name '*.c')
# Object files
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Targets
TARGET = my_program

# Default target
all: $(TARGET)

# Compile .c files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Export shared library target
export: $(filter-out $(wildcard $(OBJDIR)/main.o), $(filter-out $(wildcard $(OBJDIR)/src/scene/scenes/*.o), $(OBJS)))
	$(CC) $(CFLAGS) -o libsimpengine.so $^

# Run target
run: $(TARGET)
	./$(TARGET)

# Valgrind target
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Open all .c and .h files recursively using Neovim
edit:
	nvim $(SRCS) $(HDRS)

print:
	echo $(SRCS)

# Clean target
clean:
	rm -rf $(OBJDIR) $(TARGET) libsimpengine.so

.PHONY: all clean
