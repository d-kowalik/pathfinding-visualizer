#pragma once

#include "Font.hpp"
#include "ShaderProgram.hpp"
#include "Text.hpp"

namespace sge::Graphics {
  class FontRenderer {
    Font _font;
    Ref<ShaderProgram> _program;
    unsigned _vao, _vbo;

  public:
    FontRenderer(const Font& font, const Ref<ShaderProgram> program);

    void Render(const Text& text);
    glm::vec2 CheckSize(const Text& text);
    const Font& GetFont() const { return _font; }
  };
}