#include <cstdio>

#include <Application.hpp>
#include <Graphics/Window.hpp>
#include <Input/Input.hpp>

#include "Point.hpp"
#include "Board.hpp"
#include "Dijkstra.hpp"
#include "AStar.hpp"

using namespace sge;


class Program : public sge::Application {
  using sge::Application::Application;

  static constexpr float TOP_BOUND = 66.f;

  int field_size = 32.0f;
  int margin = 6.0f;
  int fields_w = 0, fields_h = 0;
  float timer = 0.f;
  bool found = false;
  bool _started = false;
  Board *_board;
  Dijkstra *_dijkstra;
  Point _src, _dest;

  bool OnCreate() override {
    int w = Window::Instance()->GetWidth();
    int h = Window::Instance()->GetHeight() - TOP_BOUND;
    fields_w = w / (field_size + margin);
    fields_h = h / (field_size + margin);

    _src = {3, 3};
    _dest = {30, 16};

    _board = new Board{fields_w, fields_h};
    _dijkstra = new Dijkstra(_board, _src, _dest);

    return true;
  }

  bool OnUpdate(float delta) override {
    if (Input::IsKeyPressed(Key::ESCAPE)) Window::Instance()->Close();
    if (Input::IsKeyPressed(Key::SPACE)) _started = true;

    DrawButton("Dijkstra", {0, 720 - TOP_BOUND}, {150, TOP_BOUND}, {.5f, .8f, .5f}, {.0f, .0f, .0f},
        [&](float, float) {
      _dijkstra = new Dijkstra(_board, _src, _dest);
    });
    DrawButton("A*", {150 + 10, 720 - TOP_BOUND}, {150, TOP_BOUND}, {.3f, .7f, .3f}, {.0f, .0f, .0f},
        [&](float, float) {
        _dijkstra = new AStar(_board, _src, _dest);
    });

    auto src = _dijkstra->GetSrc();
    auto dest = _dijkstra->GetDest();

    for (int y = 0; y < fields_h; y++) {
      for (int x = 0; x < fields_w; x++) {
        if (x == src.x && y == src.y) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.9f, .0f, .6f});
        } else if (x == dest.x && y == dest.y) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.9f, .4f, .6f});
        } else if (_dijkstra->OnFinalPath(x, y)) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.7f, .7f, .0f});
        } else if (!_board->Free(x, y)) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.0f, .0f, .0f},
                        [=](float _1, float _2) {
                          _board->SetFree(x, y);
                        });
        } else if (_dijkstra->Visited(x, y)) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.6f, .4f, .9f});
        } else {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.0f, .8f, .3f},
                        [=](float _1, float _2) {
                          _board->SetWall(x, y);
                        });
        }
      }
    }

    if (timer < 1.0f)
      timer += delta * 100;
    while (_started && timer > 1.0f) {
      timer -= 1.f;
      _dijkstra->Tick();
    }

    return true;
  }
};

int main() {
  Program program{"Pathfinding Visualizer", 1280, 720};
  program.Run();

  return 0;
}