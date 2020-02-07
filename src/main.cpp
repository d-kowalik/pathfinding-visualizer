#include <cstdio>

#include <Application.hpp>
#include <Graphics/Window.hpp>
#include <Input/Input.hpp>

#include "Point.hpp"
#include "Board.hpp"
#include "Dijkstra.hpp"
#include "AStar.hpp"
#include "DFS.hpp"
#include "AStar2.hpp"

using namespace sge;


class Program : public sge::Application {
  using sge::Application::Application;

  static constexpr float TOP_BOUND = 66.f;

  float field_size = 20.0f;
  int cells_horizontally = 88, cells_vertically;
  float margin = 2.f;
  float timer = 0.f;
  bool found = false;
  bool _started = false;
  Board *_board;
  Dijkstra *_dijkstra;
  Point _src, _dest;
  bool** _already_clicked;
  bool _mouse_button_released = false;
  Graphics::Button bfs_button{};
  Graphics::Button dijkstra_button{};
  Graphics::Button astar_button{};
  Graphics::Button astar2_button{};
  Graphics::Button dfs_button{};

  ~Program() override {
    DestroyField();
  }

  void DestroyField() {
    delete _board;
    delete _dijkstra;
    delete[] _already_clicked;
  }

  void InitializeField() {
    int w = Window::Instance()->GetWidth();
    int h = Window::Instance()->GetHeight() - TOP_BOUND;
    field_size = (float)w / (float)(cells_horizontally) - margin;
    cells_vertically = (float)h / (field_size + margin);

    _src = {std::max(0, 4), cells_vertically/2};
    _dest = {std::max(1, cells_horizontally - 5), cells_vertically/2};

    _board = new Board{cells_horizontally, cells_vertically};
    _dijkstra = new Dijkstra(_board, _src, _dest);

    _already_clicked = new bool*[cells_horizontally];
    for (int i = 0; i < cells_horizontally; i++) _already_clicked[i] = new bool[cells_vertically];
  }


  bool OnCreate() override {
    int w = Window::Instance()->GetWidth();
    int h = Window::Instance()->GetHeight() - TOP_BOUND;
    field_size = (float)w / (float)(cells_horizontally) - margin;
    cells_vertically = (float)h / (field_size + margin);

    _src = {std::max(0, 4), cells_vertically/2};
    _dest = {std::max(1, cells_horizontally - 5), cells_vertically/2};

    _board = new Board{cells_horizontally, cells_vertically};
    _dijkstra = new Dijkstra(_board, _src, _dest);
    _already_clicked = new bool*[cells_horizontally];
    for (int i = 0; i < cells_horizontally; i++) _already_clicked[i] = new bool[cells_vertically];

    dijkstra_button.text = "Dijkstra";
    dijkstra_button.text_color = {.0f, .0f, .0f};
    dijkstra_button.text_scale = 0.75f;
    dijkstra_button.fill_color = {.5f, .8f, .5f};
    dijkstra_button.position = {0+5, 720 - TOP_BOUND};
    dijkstra_button.scale = {150, TOP_BOUND-5};
    dijkstra_button.is_toggle_button = true;
    dijkstra_button.toggled = true;
    dijkstra_button.toggled_color = {.15f, .3f, .6f};
    dijkstra_button.callback += [=](float, float) {
      delete _dijkstra;
      _dijkstra = new Dijkstra(_board, _src, _dest);
    };

    astar_button.text = "A* 1";
    astar_button.text_color = {.0f, .0f, .0f};
    astar_button.text_scale = 0.75f;
    astar_button.fill_color = {.5f, .8f, .5f};
    astar_button.position = {150+5+5, 720 - TOP_BOUND};
    astar_button.scale = {150, TOP_BOUND-5};
    astar_button.is_toggle_button = true;
    astar_button.toggled_color = {.15f, .3f, .6f};
    astar_button.callback += [=](float, float) {
      delete _dijkstra;
      _dijkstra = new AStar(_board,  _src, _dest);
    };

    astar2_button.text = "A* 2";
    astar2_button.text_color = {.0f, .0f, .0f};
    astar2_button.text_scale = 0.75f;
    astar2_button.fill_color = {.5f, .8f, .5f};
    astar2_button.position = {150+150+5+5+5, 720 - TOP_BOUND};
    astar2_button.scale = {150, TOP_BOUND-5};
    astar2_button.is_toggle_button = true;
    astar2_button.toggled_color = {.15f, .3f, .6f};
    astar2_button.callback += [=](float, float) {
      delete _dijkstra;
      _dijkstra = new AStar2(_board,  _src, _dest);
    };

    bfs_button.text = "BFS";
    bfs_button.text_color = {.0f, .0f, .0f};
    bfs_button.text_scale = 0.75f;
    bfs_button.fill_color = {.5f, .8f, .5f};
    bfs_button.position = {150+150+150+5+5+5+5, 720 - TOP_BOUND};
    bfs_button.scale = {150, TOP_BOUND-5};
    bfs_button.is_toggle_button = true;
    bfs_button.toggled_color = {.15f, .3f, .6f};
    bfs_button.callback += [=](float, float) {
      delete _dijkstra;
      _dijkstra = new Dijkstra(_board,  _src, _dest);
    };

    dfs_button.text = "DFS";
    dfs_button.text_color = {.0f, .0f, .0f};
    dfs_button.text_scale = 0.75f;
    dfs_button.fill_color = {.5f, .8f, .5f};
    dfs_button.position = {150+150+150+150+5+5+5+5+5, 720 - TOP_BOUND};
    dfs_button.scale = {150, TOP_BOUND-5};
    dfs_button.is_toggle_button = true;
    dfs_button.toggled_color ={.15f, .3f, .6f};
    dfs_button.callback += [=](float, float) {
      delete _dijkstra;
      _dijkstra = new DFS(_board, _src, _dest);
    };


    return true;
  }

  void DrawField(Graphics::Rectangle& rectangle, glm::vec2 position) {
    rectangle.position = position;
    DrawRectangle(rectangle);
  }

  void OnKeyPressed(Key key) override {
    if (key == Key::P) {
      _started = !_started;
    } else if (key == Key::R) {
      _board->Reset();
    } else if (key == Key::SPACE) {
      if (_started) {
        _started = false;
        _dijkstra->Reset();
      } else {
        _started = true;
      }
    } else if (!_started && key == Key::KP_ADD) {
      DestroyField();
      margin -= 0.01f;
      cells_horizontally += 2;
      InitializeField();
    } else if (!_started && key == Key::KP_SUBTRACT && cells_horizontally > 5) {
      DestroyField();
      margin += 0.01f;
      cells_horizontally -= 2;
      InitializeField();
    }
  }

  bool OnUpdate(float delta) override {
    if (Input::IsKeyPressed(Key::ESCAPE)) Window::Instance()->Close();

    if (Input::IsMouseButtonPressed(MouseButton::B1)) {
      _mouse_button_released = false;
      const auto mouse_position = Input::GetMousePos();
      printf("(%f, %f)\n", mouse_position.x, mouse_position.y);
      int x = mouse_position.x / Window::Instance()->GetWidth() * cells_horizontally + margin/cells_horizontally;
      int y = (Window::Instance()->GetHeight() - mouse_position.y) / (Window::Instance()->GetHeight() - TOP_BOUND) * cells_vertically;
      if (_board->InBounds(x, y) && !_already_clicked[x][y]) {
        _already_clicked[x][y] = true;
          if (!_started && Input::IsKeyPressed(Key::LEFT_CONTROL)) {
            _dijkstra->SetSource({x, y});
            _src = {x, y};
          } else if (!_started && Input::IsKeyPressed(Key::LEFT_SHIFT)) {
            _dijkstra->SetDestination({x, y});
            _dest = {x, y};
          } else {
            if (_board->Free(x, y)) {
              _board->SetWall(x, y);
            } else {
              _board->SetFree(x, y);
            }
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

    Graphics::Rectangle free_tile{};
    free_tile.scale = {field_size, field_size};
    free_tile.color = {.6f, .4f, .9f};

    DrawButton(dijkstra_button);
    DrawButton(astar_button);
    DrawButton(astar2_button);
    DrawButton(bfs_button);
    DrawButton(dfs_button);

    for (int y = 0; y < cells_vertically; y++) {
      for (int x = 0; x < cells_horizontally; x++) {
        const glm::vec2 position{(margin * (x + 1) + field_size * x), (margin * (y + 1) + field_size * y)};
        if (x == src.x && y == src.y) {
          DrawField(source_rectangle, position);
        } else if (x == dest.x && y == dest.y) {
          DrawField(destination_rectangle, position);
        } else if (_dijkstra->OnFinalPath(x, y)) {
          DrawField(path_rectangle, position);
        } else if (!_board->Free(x, y)) {
          DrawField(wall_tile, position);
        } else if (_dijkstra->Visited(x, y)) {
          DrawField(visited_tile, position);
        } else {
          DrawField(free_tile, position);
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