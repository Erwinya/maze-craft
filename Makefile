CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2
CPPFLAGS = -Iinclude
TARGET = maze-craft
SRCS = src/main.cpp src/maze.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean sample

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

src/%.o: src/%.cpp include/maze.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

sample: $(TARGET)
	./$(TARGET) --width 21 --height 11 --seed 7

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
