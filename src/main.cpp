#include "maze.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    int width = 31;
    int height = 21;
    unsigned seed = 42;
    bool solve = true;
    std::string svg_path;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--width" && i + 1 < argc) {
            width = std::stoi(argv[++i]);
        } else if (arg == "--height" && i + 1 < argc) {
            height = std::stoi(argv[++i]);
        } else if (arg == "--seed" && i + 1 < argc) {
            seed = static_cast<unsigned>(std::stoul(argv[++i]));
        } else if (arg == "--no-solve") {
            solve = false;
        } else if (arg == "--svg" && i + 1 < argc) {
            svg_path = argv[++i];
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "Usage: maze-craft [--width W] [--height H] [--seed N] [--no-solve] [--svg out.svg]\n";
            return 0;
        } else {
            std::cerr << "unknown argument: " << arg << '\n';
            return 2;
        }
    }

    try {
        mazecraft::Maze maze = mazecraft::generate(width, height, seed);
        if (solve && !mazecraft::solve_bfs(maze)) {
            std::cerr << "warning: no path found\n";
        }
        std::cout << mazecraft::to_ascii(maze);
        if (!svg_path.empty()) {
            std::ofstream out(svg_path);
            if (!out) {
                std::cerr << "cannot write " << svg_path << '\n';
                return 2;
            }
            out << mazecraft::to_svg(maze);
            std::cerr << "wrote " << svg_path << '\n';
        }
        return 0;
    } catch (const std::exception &ex) {
        std::cerr << "error: " << ex.what() << '\n';
        return 1;
    }
}
