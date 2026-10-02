#include "maze.hpp"

#include <algorithm>
#include <random>
#include <sstream>
#include <stack>
#include <stdexcept>

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

bool solve_bfs(Maze & /*maze*/) {
    throw std::runtime_error("solve_bfs() not implemented yet");
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

std::string to_svg(const Maze & /*maze*/, int /*scale*/) {
    throw std::runtime_error("to_svg() not implemented yet");
}

}  // namespace mazecraft
