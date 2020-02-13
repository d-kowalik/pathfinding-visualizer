#pragma once

#include <glm/vec2.hpp>

#include "Keycodes.hpp"

namespace sge {

  class Input {
  public:
    static bool IsKeyPressed(Key key);
    static bool IsMouseButtonPressed(MouseButton button);
    static glm::vec2 GetMousePos();
  };

}


