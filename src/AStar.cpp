//
// Created by damian on 26.01.2020.
//

#include "AStar.hpp"

bool AStar::Check(int x, int y, Point current_point, bool diag = false) {
  if (_board->InBounds(x, y) && !_visited[x][y]) {
    _visited[x][y] = true;
    if (x == _dest.x && y == _dest.y) {
      printf("Found! Distance: %f\n", current_point.distance + 1);
      _previous_points[x][y] = std::make_pair(current_point.x, current_point.y);
      CalculatePath();
      return true;
    }
    if (_board->Free(x, y)) {
      _next_points.emplace(x, y, current_point.g + (diag ? std::sqrt(2) : 1.0f), CalculateHValue(x, y));
      _previous_points[x][y] = std::make_pair(current_point.x, current_point.y);
    }
  }
  return false;
}


float AStar::CalculateHValue(int row, int col) {
  return ((float)std::sqrt ((row-_dest.x)*(row-_dest.x)
                            + (col-_dest.y)*(col-_dest.y)));
}