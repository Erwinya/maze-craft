# maze-craft

Maze generator (DFS recursive backtracker) and BFS solver in **C++17**.

Outputs ASCII and optional SVG.

## Status

Complete: library, CLI (`--stats`), smoke tests, build scripts (`Makefile`, `build.bat`), and CI.

## Build

```bash
make
make test
./maze-craft --width 21 --height 11 --seed 7 --stats
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
std::size_t steps = mazecraft::path_length(maze);
```


## ASCII legend

| Char | Meaning |
|------|---------|
| `#` | Wall |
| ` ` (space) | Passage |
| `.` | Solved path |
| `S` | Start |
| `G` | Goal |

## Requirements

- C++17 compiler

## License

MIT
