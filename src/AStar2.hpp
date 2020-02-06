#pragma once

#include "AStar.hpp"

class AStar2 : public Dijkstra {
  using Dijkstra::Dijkstra;

  float CalculateDistance(int x, int y, Point current_point, bool diag = false) override {
    return (_dest.x - x)*(_dest.x - x) + (_dest.y - y)*(_dest.y - y);
  }
};