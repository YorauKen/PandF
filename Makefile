# Compiler
CXX = g++
CXXFLAGS = -std=c++20 -Wall  -w

# Source files
SOURCES = main.cpp csv_reader.cpp dataframe.cpp Column.cpp Index.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable target
TARGET = op

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

RMFILE = rm -f
ifeq ($(OS),Windows_NT)
    RMFILE = del
endif
# Clean target
clean:
	$(RMFILE)  $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean