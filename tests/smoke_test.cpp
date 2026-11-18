#include "maze.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

int fail(const std::string &message) {
    std::cerr << "FAIL: " << message << '\n';
    return 1;
}

}  // namespace

int main() {
    // Deterministic generate + solve for several seeds.
    for (unsigned seed : {1u, 7u, 42u, 99u}) {
        mazecraft::Maze maze = mazecraft::generate(21, 11, seed);
        if (maze.at(maze.start.first, maze.start.second) != mazecraft::Cell::Start) {
            return fail("missing start for seed " + std::to_string(seed));
        }
        if (maze.at(maze.goal.first, maze.goal.second) != mazecraft::Cell::Goal) {
            return fail("missing goal for seed " + std::to_string(seed));
        }
        if (!mazecraft::solve_bfs(maze)) {
            return fail("unsolvable maze for seed " + std::to_string(seed));
        }
        if (mazecraft::path_length(maze) < 3) {
            return fail("path too short for seed " + std::to_string(seed));
        }
        const std::string ascii = mazecraft::to_ascii(maze);
        if (ascii.find('S') == std::string::npos || ascii.find('G') == std::string::npos) {
            return fail("ascii missing S/G for seed " + std::to_string(seed));
        }
    }

    // Even inputs are normalized to odd dimensions (>= 5).
    mazecraft::Maze normalized = mazecraft::generate(20, 10, 3);
    if (normalized.width % 2 == 0 || normalized.height % 2 == 0) {
        return fail("dimensions should be forced odd");
    }
    if (normalized.width < 5 || normalized.height < 5) {
        return fail("dimensions should be at least 5");
    }

    std::cout << "smoke_test: ok\n";
    return 0;
}
