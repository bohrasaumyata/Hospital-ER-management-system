# Compiler to use
CC = gcc

# Compiler flags (options)
# -Wall = Show all warnings, which is good practice
# -g = Include debugging information
CFLAGS = -Wall -g

# List all your .c source files
SOURCES = main.c menu.c patientadd.c patientdis.c search.c display.c

# List all the .o object files (derived from the .c files)
OBJECTS = $(SOURCES:.c=.o)

# The name of your final executable program
TARGET = main

# --- Rules ---

# Default rule: This runs when you just type 'make'
all: $(TARGET)

# Rule to link all .o files into the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile a .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up compiled files
clean:
	rm -f $(OBJECTS) $(TARGET)