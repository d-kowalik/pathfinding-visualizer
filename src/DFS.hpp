#pragma once

#include "Dijkstra.hpp"

class DFS : public Dijkstra {
  std::stack<Point> _dfs_stack{};

public:
  DFS(Board *board, Point src, Point dest) : Dijkstra(board, src, dest) {
    Reset(board, src, dest);
  }

  void Reset(Board *board, Point src, Point dest) override {
    Dijkstra::Reset(board, src, dest);
    _dfs_stack.push(src);
    _visited[src.x][src.y] = true;
  }

  bool Check(int x, int y, Point current_point, bool diag = false) override {
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

  void Tick() override {
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
};


