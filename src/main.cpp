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
  int cells_horizontally = 66, cells_vertically;
  float margin = 2.f;
  float timer = 0.f;
  bool found = false;
  bool _started = false;
  Board *_board;
  Dijkstra *_dijkstra;
  Point _src, _dest;
  float _keypress_timeout = 1.0f;
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
    if (_keypress_timeout < 1.0f)
      _keypress_timeout += delta * 10;
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

    auto src = _dijkstra->GetSrc();
    auto dest = _dijkstra->GetDest();

    Graphics::Rectangle source_rectangle{};
    source_rectangle.scale = {field_size, field_size};
    source_rectangle.color = {.9f, .0f, .6f};

    Graphics::Rectangle destination_rectangle{};
    destination_rectangle.scale = {field_size, field_size};
    destination_rectangle.color = {.7f, .7f, .7f};

    Graphics::Rectangle path_rectangle{};
    path_rectangle.scale = {field_size, field_size};
    path_rectangle.color = {.7f, .7f, .0f};

    Graphics::Rectangle wall_tile{};
    wall_tile.scale = {field_size, field_size};
    wall_tile.color = {.0f, .0f, .0f};

    Graphics::Rectangle visited_tile{};
    visited_tile.scale = {field_size, field_size};
    visited_tile.color = {.2f, .4f, .7f};

    Graphics::Button dijkstra_button{};
    dijkstra_button.text = "Dijkstra";
    dijkstra_button.text_color = {.0f, .0f, .0f};
    dijkstra_button.text_scale = 0.75f;
    dijkstra_button.fill_color = {.5f, .8f, .5f};
    dijkstra_button.position = {0, 720 - TOP_BOUND};
    dijkstra_button.scale = {150, TOP_BOUND};

    Graphics::Button astar_button{};
    astar_button.text = "A*";
    astar_button.text_color = {.0f, .0f, .0f};
    astar_button.text_scale = 0.75f;
    astar_button.fill_color = {.5f, .8f, .5f};
    astar_button.position = {150+5, 720 - TOP_BOUND};
    astar_button.scale = {150, TOP_BOUND};

    Graphics::Button free_tile{};
    free_tile.scale = {field_size, field_size};
    free_tile.fill_color = {.6f, .4f, .9f};

    DrawButton(dijkstra_button,[=](float, float) {
      delete _dijkstra;
      _dijkstra = new Dijkstra(_board, src, dest);
    });
    DrawButton(astar_button, [=](float, float) {
      delete _dijkstra;
      _dijkstra = new AStar(_board,  src, dest);
    });

    for (int y = 0; y < cells_vertically; y++) {
      for (int x = 0; x < cells_horizontally; x++) {
        const glm::vec2 position{(margin * (x + 1) + field_size * x), (margin * (y + 1) + field_size * y)};
        if (x == src.x && y == src.y) {
          source_rectangle.position = position;
          DrawRectangle(source_rectangle);
        } else if (x == dest.x && y == dest.y) {
          destination_rectangle.position = position;
          DrawRectangle(destination_rectangle);
        } else if (_dijkstra->OnFinalPath(x, y)) {
          path_rectangle.position = position;
          DrawRectangle(path_rectangle);
        } else if (!_board->Free(x, y)) {
          wall_tile.position = position;
          DrawRectangle(wall_tile);
        } else if (_dijkstra->Visited(x, y)) {
          visited_tile.position = position;
          DrawRectangle(visited_tile);
        } else {
          free_tile.position = position;
          DrawButton(free_tile,[=](float _1, float _2) {
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