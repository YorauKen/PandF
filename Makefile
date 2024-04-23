# Compiler
CXX = g++
CXXFLAGS = -std=c++20 -Wall  -w

# Source files
SOURCES = csv_reader.cpp dataframe.cpp Column.cpp Index.cpp

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

test1: test1.cpp $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./$@

test1-error: test1-error.cpp $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./$@

test2: test2.cpp $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./$@

test3: test3.cpp $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./$@

test4: test4.cpp $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./$@
test5: test5.cpp $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./$@
test6: test6.cpp $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./$@

RMFILE = rm -f
ifeq ($(OS),Windows_NT)
    RMFILE = del
endif
# Clean target
clean:
	$(RMFILE)  $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean