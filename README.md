# maze-craft

Maze generator (DFS recursive backtracker) and BFS solver in **C++17**.

Outputs ASCII and optional SVG.

## Status

Public header, DFS `generate()`, `to_ascii()`, BFS `solve_bfs()`, and `to_svg()` are in place. CLI and build scripts will land in a follow-up commit.

## Library (so far)

```cpp
#include "maze.hpp"

auto maze = mazecraft::generate(31, 15, /*seed=*/7);
mazecraft::solve_bfs(maze);
std::cout << mazecraft::to_ascii(maze);
std::string svg = mazecraft::to_svg(maze);
```

## Requirements

- C++17 compiler

## License

MIT
