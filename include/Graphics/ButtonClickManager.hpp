#pragma once

#include "Button.hpp"

#include <vector>

namespace sge::Graphics {

  class ButtonClickManager {
    std::vector<Button*> _buttons{};

  public:
    ButtonClickManager();

    void Add(Button& button);
    void Clear();

    void HandleClick(float x, float y);
  };

}