#include "maze.hpp"

#include <algorithm>
#include <queue>
#include <random>
#include <sstream>
#include <stack>

namespace mazecraft {
namespace {

bool in_bounds(const Maze &m, int x, int y) {
    return x >= 0 && y >= 0 && x < m.width && y < m.height;
}

}  // namespace

Maze generate(int width, int height, unsigned seed) {
    if (width % 2 == 0) ++width;
    if (height % 2 == 0) ++height;
    if (width < 5) width = 5;
    if (height < 5) height = 5;

    Maze m;
    m.width = width;
    m.height = height;
    m.cells.assign(static_cast<std::size_t>(width * height), Cell::Wall);

    std::mt19937 rng(seed);
    std::stack<std::pair<int, int>> st;
    m.set(1, 1, Cell::Passage);
    st.push({1, 1});

    const int dirs[4][2] = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};
    while (!st.empty()) {
        auto [x, y] = st.top();
        std::vector<int> order = {0, 1, 2, 3};
        std::shuffle(order.begin(), order.end(), rng);
        bool moved = false;
        for (int di : order) {
            int nx = x + dirs[di][0];
            int ny = y + dirs[di][1];
            if (!in_bounds(m, nx, ny) || m.at(nx, ny) != Cell::Wall) continue;
            m.set(x + dirs[di][0] / 2, y + dirs[di][1] / 2, Cell::Passage);
            m.set(nx, ny, Cell::Passage);
            st.push({nx, ny});
            moved = true;
            break;
        }
        if (!moved) st.pop();
    }

    m.start = {1, 1};
    m.goal = {width - 2, height - 2};
    if (m.at(m.goal.first, m.goal.second) == Cell::Wall) {
        m.goal = {width - 2 - ((width - 2) % 2 == 0 ? 1 : 0),
                  height - 2 - ((height - 2) % 2 == 0 ? 1 : 0)};
        if (m.at(m.goal.first, m.goal.second) == Cell::Wall) m.goal = m.start;
    }
    m.set(m.start.first, m.start.second, Cell::Start);
    m.set(m.goal.first, m.goal.second, Cell::Goal);
    return m;
}

bool solve_bfs(Maze &maze) {
    const int w = maze.width;
    const int h = maze.height;
    std::vector<int> parent(static_cast<std::size_t>(w * h), -1);
    std::queue<std::pair<int, int>> q;
    auto id = [w](int x, int y) { return y * w + x; };

    q.push(maze.start);
    parent[id(maze.start.first, maze.start.second)] = id(maze.start.first, maze.start.second);

    const int step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool found = false;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == maze.goal.first && y == maze.goal.second) {
            found = true;
            break;
        }
        for (auto &d : step) {
            int nx = x + d[0];
            int ny = y + d[1];
            if (!in_bounds(maze, nx, ny)) continue;
            Cell c = maze.at(nx, ny);
            if (c == Cell::Wall) continue;
            if (parent[id(nx, ny)] != -1) continue;
            parent[id(nx, ny)] = id(x, y);
            q.push({nx, ny});
        }
    }
    if (!found) return false;

    int cur = id(maze.goal.first, maze.goal.second);
    int start_id = id(maze.start.first, maze.start.second);
    while (cur != start_id) {
        int x = cur % w;
        int y = cur / w;
        if (!(x == maze.goal.first && y == maze.goal.second) &&
            !(x == maze.start.first && y == maze.start.second)) {
            maze.set(x, y, Cell::Path);
        }
        cur = parent[cur];
    }
    maze.set(maze.start.first, maze.start.second, Cell::Start);
    maze.set(maze.goal.first, maze.goal.second, Cell::Goal);
    return true;
}

std::string to_ascii(const Maze &maze) {
    std::ostringstream out;
    for (int y = 0; y < maze.height; ++y) {
        for (int x = 0; x < maze.width; ++x) {
            out << static_cast<char>(maze.at(x, y));
        }
        out << '\n';
    }
    return out.str();
}

std::string to_svg(const Maze &maze, int scale) {
    std::ostringstream out;
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << maze.width * scale
        << "\" height=\"" << maze.height * scale << "\">\n";
    out << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
    for (int y = 0; y < maze.height; ++y) {
        for (int x = 0; x < maze.width; ++x) {
            Cell c = maze.at(x, y);
            const char *fill = nullptr;
            if (c == Cell::Wall) fill = "#111";
            else if (c == Cell::Path) fill = "#4ade80";
            else if (c == Cell::Start) fill = "#60a5fa";
            else if (c == Cell::Goal) fill = "#f87171";
            if (!fill) continue;
            out << "<rect x=\"" << x * scale << "\" y=\"" << y * scale << "\" width=\"" << scale
                << "\" height=\"" << scale << "\" fill=\"" << fill << "\"/>\n";
        }
    }
    out << "</svg>\n";
    return out.str();
}

}  // namespace mazecraft
