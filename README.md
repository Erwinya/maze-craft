# maze-craft

Maze generator (DFS recursive backtracker) and BFS solver in **C++17**.

Outputs ASCII and optional SVG.

## Status

Public header, DFS `generate()`, and `to_ascii()` are in place. BFS solve, SVG, CLI, and build scripts will land in follow-up commits.

## Library (so far)

```cpp
#include "maze.hpp"

auto maze = mazecraft::generate(31, 15, /*seed=*/7);
std::cout << mazecraft::to_ascii(maze);
```

## Requirements

- C++17 compiler

## License

MIT
