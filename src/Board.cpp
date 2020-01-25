//
// Created by damian on 25.01.2020.
//

#include "Board.hpp"

Board::Board(int w, int h) : _w{w}, _h{h} {
  _graph = std::vector<std::vector<int>>(w, std::vector<int>(h, 1));
}

bool Board::InBounds(int x, int y) const {
  return x>= 0 && y >= 0 && x < _w && y < _h;
}

bool Board::Free(int x, int y) const {
  return _graph[x][y];
}
