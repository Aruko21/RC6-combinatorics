# Exec file name
TARGET = lab4

# cc invoking
CC = g++

# standard definition
STD = c++11

# object file names
OBJECTS = src/main.o

# source files directory
SRCS = src/

# project dependence
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

# $< means first dependent argument. Example: all: obj obj2 - $< = obj
# $@ means target. For previous example this is "all"
# rule for implicit handling of all object files
%.o: %.cpp
	$(CC) -c $< -o $@ --std=$(STD)
clean:
	rm -rf $(TARGET) $(SRCS)*.o
