#pragma once

#include <vector>

class Board {
  std::vector<std::vector<int>> _graph;
  int _w, _h;

public:
  Board(int w, int h);

  inline int GetWidth() const { return _w; }
  inline int GetHeight() const { return _h; }

  bool InBounds(int x, int y) const;
  bool Free(int x, int y) const;

  void SetWall(int x, int y) {
    _graph[x][y] = 0;
  }

  void SetFree(int x, int y) {
    _graph[x][y] = 1;
  }
};


