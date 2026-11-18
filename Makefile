CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2
CPPFLAGS = -Iinclude
TARGET = maze-craft
TEST_TARGET = smoke_test
SRCS = src/main.cpp src/maze.cpp
LIB_SRCS = src/maze.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean sample test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

src/%.o: src/%.cpp include/maze.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TEST_TARGET): tests/smoke_test.cpp $(LIB_SRCS) include/maze.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ tests/smoke_test.cpp $(LIB_SRCS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

sample: $(TARGET)
	./$(TARGET) --width 21 --height 11 --seed 7

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe $(TEST_TARGET) $(TEST_TARGET).exe
