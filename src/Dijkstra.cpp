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
  _board->Reset();
  Reset(_board, src, dest);
}

void Dijkstra::Reset() {
  Reset(_src, _dest);
}
