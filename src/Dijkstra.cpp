#include "Dijkstra.hpp"

Dijkstra::Dijkstra(Board* board, Point src, Point dest) : _board{board}, _src{src}, _dest{dest} {
  Reset(board, src, dest);
}

void Dijkstra::Reset(Board* board, Point src, Point dest) {
  _board = board;
  _src = src;
  _dest = dest;
  _final_path.clear();
  _next_points.clear();
  _found = false;
  _visited = std::vector<std::vector<bool>>(board->GetWidth(), std::vector<bool>(board->GetHeight(), false));
  _previous_points = std::vector<std::vector<std::pair<int, int>>>(board->GetWidth(),
                                                                   std::vector<std::pair<int, int>>(board->GetHeight()));
  _next_points.emplace(_src.x, _src.y);
}

void Dijkstra::Reset(Point src, Point dest) {
  Reset(_board, src, dest);
}

void Dijkstra::Reset() {
  Reset(_src, _dest);
}

bool Dijkstra::Check(int x, int y, Point current_point, bool diag = false) {
  if (_board->InBounds(x, y) && !_visited[x][y]) {
    _visited[x][y] = true;
    if (x == _dest.x && y == _dest.y) {
      printf("Found! Distance: %f\n", current_point.distance + 1);
      _previous_points[x][y] = std::make_pair(current_point.x, current_point.y);
      CalculatePath();
      return true;
    }
    if (_board->Free(x, y)) {
      _next_points.emplace(x, y, CalculateDistance(x, y, current_point, diag));
      _previous_points[x][y] = std::make_pair(current_point.x, current_point.y);
    }
  }
  return false;
}

void Dijkstra::CalculatePath() {
  std::stack<std::pair<int, int>> path{};
  int x = _dest.x;
  int y = _dest.y;
  while (x != _src.x || y != _src.y) {
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

void Dijkstra::Tick() {
  if (!_next_points.empty() && !_found) {
    Point current_point = *_next_points.begin();
    _next_points.erase(_next_points.begin());
    int x = current_point.x;
    int y = current_point.y;
    int dist = current_point.distance;
    _visited[x][y] = true;

    // Search right
    if (!_found && Check(x + 1, y, current_point))
      _found = true;
    // Search left
    if (!_found && Check(x - 1, y, current_point))
      _found = true;
    // Search down
    if (!_found && Check(x, y + 1, current_point))
      _found = true;
    // Search up
    if (!_found && Check(x, y - 1, current_point))
      _found = true;
    if (!_found && Check(x + 1, y + 1, current_point, true))
      _found = true;
    if (!_found && Check(x + 1, y - 1, current_point, true))
      _found = true;
    if (!_found && Check(x - 1, y + 1, current_point, true))
      _found = true;
    if (!_found && Check(x - 1, y - 1, current_point, true))
      _found = true;
  }
}