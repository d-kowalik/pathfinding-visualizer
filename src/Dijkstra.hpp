#pragma once

#include "Point.hpp"
#include "Board.hpp"

#include <vector>
#include <set>
#include <stack>
#include <utility>
#include <algorithm>

class Dijkstra {
  Board* _board;
  std::vector<std::vector<bool>> _visited;
  std::set<Point> _next_points{};
  std::vector<std::vector<std::pair<int, int>>> _previous_points;
  std::vector<std::pair<int, int>> _final_path{};
  Point _src, _dest;
  bool _found = false;

public:
  Dijkstra(Board* board, Point src, Point dest);

  inline Point GetSrc() { return _src; }
  inline Point GetDest() { return _dest; }

  bool OnFinalPath(int x, int y) {
    return std::find(_final_path.begin(), _final_path.end(), std::make_pair(x, y)) != _final_path.end();
  }

  bool Visited(int x, int y) const {
    return _visited[x][y];
  }

  bool Check(int x, int y, int current_x, int current_y, int dist) {
    if (_board->InBounds(x, y) && !_visited[x][y]) {
      _visited[x][y] = true;
      if (x == _dest.x && y == _dest.y) {
        printf("Found! Distance: %d\n", dist + 1);
        _previous_points[x][y] = std::make_pair(current_x, current_y);
        CalculatePath(dist + 1);
        return true;
      }
      if (_board->Free(x, y)) {
        _next_points.emplace(x, y, dist + 1);
        _previous_points[x][y] = std::make_pair(current_x, current_y);
      }
    }
    return false;
  }

  void CalculatePath(int dist) {
    dist += 1;
    std::stack<std::pair<int, int>> path{};
    int x = _dest.x;
    int y = _dest.y;
    while (dist--) {
      path.emplace(x, y);
      _final_path.emplace_back(x, y);
      auto next_pair = _previous_points[x][y];
      x = next_pair.first;
      y = next_pair.second;
    }

    std::pair<int, int> node = path.top();
    path.pop();
    printf("(%d, %d)", node.first, node.second);

    while (!path.empty()) {
      node = path.top();
      path.pop();
      printf(" -> (%d, %d)", node.first, node.second);
    }
    putchar('\n');
  }

  void Tick() {
    if (!_next_points.empty() && !_found) {
      Point current_point = *_next_points.begin();
      _next_points.erase(_next_points.begin());
      int x = current_point.x;
      int y = current_point.y;
      int dist = current_point.distance;
      _visited[x][y] = true;

      // Search right
      if (!_found && Check(x + 1, y, x, y, dist))
        _found = true;
      // Search left
      if (!_found && Check(x - 1, y, x, y, dist))
        _found = true;
      // Search down
      if (!_found && Check(x, y + 1, x, y, dist))
        _found = true;
      // Search up
      if (!_found && Check(x, y - 1, x, y, dist))
        _found = true;
    }
  }
};


