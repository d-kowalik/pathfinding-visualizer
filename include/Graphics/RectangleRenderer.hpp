#pragma once

#include "ShaderProgram.hpp"

#include "Rectangle.hpp"

namespace sge::Graphics {
  class RectangleRenderer {
    unsigned _vao, _vbo, _ebo;
    unsigned indices[6] = {
        0, 1, 3,
        1, 2, 3
    };
    Ref<ShaderProgram> _program;

  public:
    explicit RectangleRenderer(const Ref<ShaderProgram> program);

    void Draw(const Rectangle& rectangle);
  };
}


