#pragma once

struct Point {
  Point() = default;

  Point(int x, int y) : x(x), y(y) {}

  Point(int x, int y, float dist) : x(x), y(y), distance(dist) {}
  Point(int x, int y, float g, float h) : x(x), y(y), g{g}, h{h} {
    distance = g + h;
  }

  int x, y;
  float distance = 0, g = 0, h = 0;

  friend bool operator<(const Point &l, const Point &r) {
    return l.distance <= r.distance;
  }
};