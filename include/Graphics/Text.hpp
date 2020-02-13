#pragma once

#include "TextDefaults.hpp"

namespace sge::Graphics {
  struct Text {
    std::string text{};
    glm::vec2 position;
    glm::vec3 color;
    float scale;
  };
}