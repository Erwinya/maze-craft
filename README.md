# maze-craft

Maze generator (DFS recursive backtracker) and BFS solver in **C++17**.

Outputs ASCII and optional SVG.

## Status

Library and CLI entrypoint are in place. Makefile / `build.bat` will land in a follow-up commit.

## Build (manual)

```powershell
g++ -std=c++17 -I include -o maze-craft.exe src\maze.cpp src\main.cpp
.\maze-craft.exe --width 31 --height 15 --seed 7 --svg build\maze.svg
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
