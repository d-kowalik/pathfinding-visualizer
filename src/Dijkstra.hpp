#pragma once

#include "Point.hpp"
#include "Board.hpp"

#include <vector>
#include <set>
#include <stack>
#include <utility>
#include <algorithm>
#include <cmath>

class Dijkstra {
protected:
  Board *_board;
  std::vector<std::vector<bool>> _visited;
  std::set<Point> _next_points{};
  std::vector<std::vector<std::pair<int, int>>> _previous_points;
  std::vector<std::pair<int, int>> _final_path{};
  Point _src, _dest;
  bool _found = false;

public:
  Dijkstra(Board *board, Point src, Point dest);

  inline Point GetSrc() { return _src; }

  inline Point GetDest() { return _dest; }

  bool OnFinalPath(int x, int y) {
    return _found && std::find(_final_path.begin(), _final_path.end(), std::make_pair(x, y)) != _final_path.end();
  }

  bool Visited(int x, int y) const {
    return _board->InBounds(x, y) && _visited[x][y];
  }

  inline void SetSource(Point src) {
    _src = src;
    Reset();
  }

  inline void SetDestination(Point dest) {
    _dest = dest;
    Reset();
  }

  virtual float CalculateDistance(int x, int y, Point current_point, bool diag = false) {
    return current_point.distance + (diag ? sqrt(2.0) : 1);
  }

  virtual void Reset(Board *board, Point src, Point dest);
  void Reset(Point src, Point dest);
  void Reset();

  virtual bool Check(int x, int y, Point current_point, bool diag = false);

  void CalculatePath();

  virtual void Tick();
};


