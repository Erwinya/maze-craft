#pragma once

#include <string>
#include <utility>
#include <vector>

namespace mazecraft {

enum class Cell : char { Wall = '#', Passage = ' ', Path = '.', Start = 'S', Goal = 'G' };

struct Maze {
    int width = 0;
    int height = 0;
    std::vector<Cell> cells;  // row-major
    std::pair<int, int> start{1, 1};
    std::pair<int, int> goal{1, 1};

    Cell at(int x, int y) const { return cells[y * width + x]; }
    void set(int x, int y, Cell c) { cells[y * width + x] = c; }
};

/// Odd dimensions recommended (width/height >= 5). Implemented in a follow-up commit.
Maze generate(int width, int height, unsigned seed);

/// Mark a shortest path from start to goal. Implemented in a follow-up commit.
bool solve_bfs(Maze &maze);

std::string to_ascii(const Maze &maze);
std::string to_svg(const Maze &maze, int scale = 12);

}  // namespace mazecraft
