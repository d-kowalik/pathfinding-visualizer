#pragma once

struct Point {
  Point() = default;

  Point(int x, int y) : x(x), y(y) {}

  Point(int x, int y, int dist) : x(x), y(y), distance(dist) {}

  int x, y, distance = 0;

  friend bool operator<(const Point &l, const Point &r) {
    return l.distance <= r.distance;
  }
};