#pragma once

#include "RectangleDefaults.hpp"

#include <glm/glm.hpp>

namespace sge::Graphics {
  struct Rectangle {
    glm::vec2 scale = RectangleDefaults::SCALE;
    glm::vec2 position = RectangleDefaults::POSITION;
    glm::vec3 color = RectangleDefaults::COLOR;
  };
}