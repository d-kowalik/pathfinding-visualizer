//
// Created by damian on 30.01.2020.
//

#include "DFS.hpp"

bool DFS::Check(int x, int y, Point current_point, bool diag) {
  if (_board->InBounds(x, y) && !_visited[x][y] && _board->Free(x, y)) {
    _visited[x][y] = true;
  if (x == _dest.x && y == _dest.y) {
    printf("Found!");
    _found = true;
  } else if (_board->Free(x, y)) {
    _dfs_stack.emplace(x, y);
    _final_path.emplace_back(x, y);
  }
    return true;
  }
  return false;
}

void DFS::Tick() {
  if (!_dfs_stack.empty() && !_found) {
    Point p = _dfs_stack.top();
    int x = p.x, y = p.y;
    if (Check(x - 1, y, p)) {}
    else if (Check(x, y - 1, p)) {}
    else if (Check(x + 1, y, p)) {}
    else if (Check(x, y + 1, p)) {}
    else _dfs_stack.pop();
  }
}