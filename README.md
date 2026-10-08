# maze-craft

Maze generator (DFS recursive backtracker) and BFS solver in **C++17**.

Outputs ASCII and optional SVG.

## Status

Complete: library, CLI, and build scripts (`Makefile`, `build.bat`).

## Build

```bash
make
./maze-craft --width 21 --height 11 --seed 7
```

Windows (MinGW / LLVM):

```bat
build.bat
build\maze-craft.exe --width 21 --height 11 --seed 7 --svg build\maze.svg
```

## Library

```cpp
#include "maze.hpp"

auto maze = mazecraft::generate(31, 15, /*seed=*/7);
mazecraft::solve_bfs(maze);
std::cout << mazecraft::to_ascii(maze);
```

## Requirements

- C++17 compiler

## License

MIT
