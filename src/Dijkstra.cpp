//
// Created by damian on 25.01.2020.
//

#include "Dijkstra.hpp"

Dijkstra::Dijkstra(Board* board, Point src, Point dest) : _board{board}, _src{src}, _dest{dest} {
  _visited = std::vector<std::vector<bool>>(board->GetWidth(), std::vector<bool>(board->GetHeight(), false));
  _previous_points = std::vector<std::vector<std::pair<int, int>>>(board->GetWidth(),
                                                                  std::vector<std::pair<int, int>>(board->GetHeight()));
  _next_points.emplace(_src.x, _src.y);
}
