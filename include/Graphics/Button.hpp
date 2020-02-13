#pragma once

#include "ButtonDefaults.hpp"
#include "../Util/Callback.hpp"

namespace sge::Graphics {
  struct Button {
    virtual ~Button() = default;
    std::string text{};
    glm::vec2 scale = ButtonDefaults::SCALE;
    glm::vec2 position = ButtonDefaults::POSITION;
    float text_scale = ButtonDefaults::TEXT_SCALE;
    glm::vec3 text_color = ButtonDefaults::TEXT_COLOR;
    glm::vec3 fill_color = ButtonDefaults::FILL_COLOR;
    glm::vec3 pressed_color = ButtonDefaults::PRESSED_COLOR;
    bool is_toggle_button = ButtonDefaults::IS_TOGGLE_BUTTON;
    bool toggled = ButtonDefaults::TOGGLED;
    glm::vec3 toggled_color = ButtonDefaults::TOGGLED_COLOR;
    Util::Callback<float, float> callback;
  };
}