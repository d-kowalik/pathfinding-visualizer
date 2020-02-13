#pragma once

#include "FontRenderer.hpp"
#include "RectangleRenderer.hpp"
#include "Button.hpp"

namespace sge::Graphics {
  class ButtonRenderer {
    Ref<FontRenderer> _font_renderer;
    Ref<RectangleRenderer> _rectangle_renderer;

  public:
    ButtonRenderer(Ref<FontRenderer> font_renderer, Ref<RectangleRenderer> rectangle_renderer);

    void DrawButton(const Button& button);
  };

}

