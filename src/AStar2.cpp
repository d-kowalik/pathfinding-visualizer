//
// Created by damian on 06.02.2020.
//

#include "AStar2.hpp"

float AStar2::CalculateDistance(int x, int y, Point current_point, bool diag) {
  return (_dest.x - x) * (_dest.x - x) + (_dest.y - y) * (_dest.y - y);
}