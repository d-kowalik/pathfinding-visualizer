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

  float field_size = 32.0f;
  int cells_horizontally = 100, cells_vertically;
  int margin = .0f;
  float timer = 0.f;
  bool found = false;
  bool _started = false;
  Board *_board;
  Dijkstra *_dijkstra;
  Point _src, _dest;
  float _keypress_timeout = 1.0f;
  float click_cooldown = 1.0f;
  bool** _already_clicked;
  bool _mouse_button_released = false;

  bool OnCreate() override {
    int w = Window::Instance()->GetWidth();
    int h = Window::Instance()->GetHeight() - TOP_BOUND;
    field_size = (float)w / (float)(cells_horizontally + 2*margin);
    cells_vertically = h / (field_size + margin);

    _src = {3, 3};
    _dest = {30, 16};

    _board = new Board{cells_horizontally, cells_vertically};
    _dijkstra = new Dijkstra(_board, _src, _dest);
    _already_clicked = new bool*[cells_horizontally];
    for (int i = 0; i < cells_horizontally; i++) _already_clicked[i] = new bool[cells_vertically];

    return true;
  }

  bool OnUpdate(float delta) override {
    if (Input::IsKeyPressed(Key::ESCAPE)) Window::Instance()->Close();
    if (Input::IsKeyPressed(Key::SPACE)) {
      if (_keypress_timeout >= 1.0f) {
        _keypress_timeout -= 1.0f;
        if (_started) {
          _dijkstra->Reset();
          _started = false;
        } else {
          _started = true;
        }
      }
    }
    if (click_cooldown < 1.0f) click_cooldown += delta * 5.f;

    if (Input::IsMouseButtonPressed(MouseButton::B1)) {
      _mouse_button_released = false;
      const auto mouse_position = Input::GetMousePos();
      int x = mouse_position.x / Window::Instance()->GetWidth() * cells_horizontally;
      int y = (Window::Instance()->GetHeight() - mouse_position.y) / (Window::Instance()->GetHeight() - TOP_BOUND) *
              cells_vertically;
      if (_board->InBounds(x, y) && !_already_clicked[x][y]) {
        _already_clicked[x][y] = true;
        if (_board->Free(x, y)) {
          _board->SetWall(x, y);
        } else {
          _board->SetFree(x, y);
        }
      }
    } else _mouse_button_released = true;

    if (_mouse_button_released) {
      _mouse_button_released = false;
      for (int i = 0; i < cells_horizontally; i++) memset(_already_clicked[i], false, cells_vertically);

    }

    if (_keypress_timeout < 1.0f)
      _keypress_timeout += delta * 10;

    auto src = _dijkstra->GetSrc();
    auto dest = _dijkstra->GetDest();

    DrawButton("Dijkstra", {0, 720 - TOP_BOUND}, {150, TOP_BOUND}, {.5f, .8f, .5f}, {.0f, .0f, .0f},
        [=](float, float) {
      delete _dijkstra;
      _dijkstra = new Dijkstra(_board, src, dest);
    });
    DrawButton("A*", {150 + 10, 720 - TOP_BOUND}, {150, TOP_BOUND}, {.3f, .7f, .3f}, {.0f, .0f, .0f},
        [=](float, float) {
      delete _dijkstra;
      _dijkstra = new AStar(_board,  src, dest);
    });

    for (int y = 0; y < cells_vertically; y++) {
      for (int x = 0; x < cells_horizontally; x++) {
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
                                                   (margin * (y + 1) + field_size * y)}, {.0f, .0f, .0f});
        } else if (_dijkstra->Visited(x, y)) {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.6f, .4f, .9f});
        } else {
          DrawRectangle({field_size, field_size}, {(margin * (x + 1) + field_size * x),
                                                   (margin * (y + 1) + field_size * y)}, {.0f, .8f, .3f},
                        [=](float _1, float _2) {
                          if (!_started) {
                            if (Input::IsKeyPressed(Key::LEFT_CONTROL)) {
                              _dijkstra->SetSource({x, y});
                              this->_src = {x, y};
                            }
                            else if (Input::IsKeyPressed(Key::LEFT_SHIFT)) {
                              _dijkstra->SetDestination({x, y});
                              this->_dest = {x, y};
                            }
                          }
                        });
        }
      }
    }

    if (timer < 1.0f)
      timer += delta * 500;
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