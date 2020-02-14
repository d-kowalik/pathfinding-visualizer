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

  bool Check(int x, int y, Point current_point, bool diag = false) override;
  void Tick() override;
};


