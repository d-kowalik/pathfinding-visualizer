#include <cstdio>

#include <Application.hpp>
#include <Graphics/Window.hpp>
#include <Input/Input.hpp>

#include "Point.hpp"

#include <set>
#include <stack>
#include <algorithm>

using namespace sge;

int size_x, size_y;
using std::set, std::pair, std::make_pair, std::stack;



bool is_in_bounds(int x, int y) {
  return x >= 0 && y >= 0 && x < size_x && y < size_y;
}

std::vector<std::vector<bool>> visited;
set<Point> next_points{};
std::vector<std::vector<pair<int, int>>> previous_points;
std::vector<pair<int, int>> final_path{};

void calculate_path(Point dest, int dist) {
  dist += 1;
  stack<pair<int, int>> path{};
  int x = dest.x;
  int y = dest.y;
  while (dist--) {
    path.emplace(x, y);
    final_path.emplace_back(x, y);
    auto next_pair = previous_points[x][y];
    x = next_pair.first;
    y = next_pair.second;
  }

  pair<int, int> node = path.top();
  path.pop();
  printf("(%d, %d)", node.first, node.second);

  while (!path.empty()) {
    node = path.top();
    path.pop();
    printf(" -> (%d, %d)", node.first, node.second);
  }
  putchar('\n');
}

bool dijkstra_check(std::vector<std::vector<int>> &graph, int x, int y, int current_x,
                    int current_y, int dist, Point dest) {
  if (is_in_bounds(x, y) && !visited[x][y]) {
    visited[x][y] = true;
    if (x == dest.x && y == dest.y) {
      printf("Found! Distance: %d\n", dist + 1);
      previous_points[x][y] = make_pair(current_x, current_y);
      calculate_path(dest, dist + 1);
      return true;
    }
    if (graph[x][y]) {
      next_points.emplace(x, y, dist + 1);
      previous_points[x][y] = make_pair(current_x, current_y);
    }
  }
  return false;
}

class Program : public sge::Application {
  using sge::Application::Application;

  std::vector<std::vector<int>> _board{};
  int field_size = 32.0f;
  int margin = 6.0f;
  int fields_w = 0, fields_h = 0;
  Point dest;
  float timer;
  bool found = false;
  bool _started = false;

  bool OnCreate() override {
    int w = Window::Instance()->GetWidth();
    int h = Window::Instance()->GetHeight();
    fields_w = w / (field_size + margin);
    fields_h = h / (field_size + margin);
    _board.reserve(fields_w);
    for (auto &board : _board) {
      board.reserve(fields_h);
    }
    size_x = fields_w;
    size_y = fields_h;

    _board = std::vector<std::vector<int>>(fields_w, std::vector<int>(fields_h, 1));
    visited = std::vector<std::vector<bool>>(fields_w, std::vector<bool>(fields_h, false));
    previous_points = std::vector<std::vector<std::pair<int, int>>>(fields_w,
                                                                    std::vector<std::pair<int, int>>(fields_h));

//    _board[3][3] = 2;

    _board[10][10] = 0;
    _board[10][11] = 0;
    _board[10][12] = 0;
    _board[10][13] = 0;
    _board[10][9] = 0;
    _board[10][8] = 0;
    _board[10][7] = 0;
    _board[10][6] = 0;
    _board[10][5] = 0;
    _board[10][4] = 0;
    _board[10][3] = 0;
    _board[10][2] = 0;

    _board[20][20] = 0;
    _board[20][19] = 0;
    _board[20][18] = 0;
    _board[20][17] = 0;
    _board[20][16] = 0;
    _board[20][15] = 0;
    _board[20][14] = 0;
    _board[20][11] = 0;
    _board[20][12] = 0;
    _board[20][13] = 0;
    _board[20][9] = 0;
    _board[20][8] = 0;
    _board[20][7] = 0;
    _board[20][6] = 0;
    _board[20][5] = 0;
    _board[20][4] = 0;
    _board[20][3] = 0;
    _board[20][2] = 0;

//    _board[13][9] = 3;

//    dijkstra(_board, {3, 3}, {13, 9});
    dest = {30, 16};
    timer = 0.f;

    next_points.emplace(12, 12);
    printf("%d\n", previous_points[0][0].first);

    return true;
  }

  bool OnUpdate(float delta) override {
    if (Input::IsKeyPressed(Key::ESCAPE)) Window::Instance()->Close();
    if (Input::IsKeyPressed(Key::A)) _camera->Move(Camera::Direction::LEFT, delta);
    if (Input::IsKeyPressed(Key::D)) _camera->Move(Camera::Direction::RIGHT, delta);
    if (Input::IsKeyPressed(Key::W)) _camera->Move(Camera::Direction::UP, delta);
    if (Input::IsKeyPressed(Key::S)) _camera->Move(Camera::Direction::DOWN, delta);
    if (Input::IsKeyPressed(Key::SPACE)) _started = true;


    DrawButton("Button", {300.f, 300.f}, {200.f, 100.f}, {.5f, .5f, .5f}, {1.f, 1.f, 1.f}, [](float, float) {
      printf("Button\n");
    });

    for (int y = 0; y < fields_h; y++) {
      for (int x = 0; x < fields_w; x++) {
        if (x == 12 && y == 12) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.9f, .0f, .6f});
        } else if (x == dest.x && y == dest.y) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.9f, .4f, .6f});
        } else if (std::find(final_path.begin(), final_path.end(), std::make_pair(x, y)) != final_path.end()) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.7f, .7f, .0f});
        } else if (_board[x][y] == 0) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.0f, .0f, .0f},
                        [=](float _1, float _2) {
                          _board[x][y] = 1;
                        });
        } else if (visited[x][y]) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.6f, .4f, .9f});
        } else {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.0f, .8f, .3f},
                        [=](float _1, float _2) {
                          _board[x][y] = 0;
                        });
        }
      }
    }

    timer += 1.f;
    if (!next_points.empty() && timer >= 1.0f && !found && _started) {
      timer -= 1.f;
      Point current_point = *next_points.begin();
      next_points.erase(next_points.begin());
      int x = current_point.x;
      int y = current_point.y;
      int dist = current_point.distance;
      visited[x][y] = true;

      // Search right
      if (!found && dijkstra_check(_board, x + 1, y, x, y, dist, dest))
        found = true;
      // Search left
      if (!found && dijkstra_check(_board, x - 1, y, x, y, dist, dest))
        found = true;
      // Search down
      if (!found && dijkstra_check(_board, x, y + 1, x, y, dist, dest))
        found = true;
      // Search up
      if (!found && dijkstra_check(_board, x, y - 1, x, y, dist, dest))
        found = true;
    }

    return true;
  }
};

int main() {
  Program program{"Pathfinding Visualizer", 1280, 720};
  program.Run();

  return 0;
}