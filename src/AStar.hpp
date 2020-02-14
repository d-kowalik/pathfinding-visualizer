#pragma once

#include "Dijkstra.hpp"

class AStar : public Dijkstra {
  using Dijkstra::Dijkstra;

  bool Check(int x, int y, Point current_point, bool diag = false) override;
  float CalculateHValue(int row, int col);
};