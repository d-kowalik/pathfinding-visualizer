#pragma once

#include <Input/Keycodes.hpp>
#include "Graphics/FontRenderer.hpp"
#include "Graphics/RectangleRenderer.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Camera.hpp"
#include "Util/Callback.hpp"
#include "Graphics/ButtonRenderer.hpp"
#include "Util/Timer.hpp"
#include "Graphics/ButtonClickManager.hpp"

namespace sge {
  class Application {
    inline static Application *_instance = nullptr;
  protected:
    Ref<Graphics::FontRenderer> _font_renderer = nullptr;
    Ref<Graphics::RectangleRenderer> _rectangle_renderer = nullptr;
    Ref<Graphics::ShaderProgram> _font_program = nullptr, _rectangle_program = nullptr;
    Ref<Graphics::ButtonRenderer> _button_renderer;
    Ref<Graphics::ButtonClickManager> _button_click_manager = nullptr;
    Ref<Camera> _camera;
    glm::mat4 _view, _model, _projection;
    Util::Timer _timer{};
  private:
    void HandleKeyPressed(Key key);
    void HandleResize(int x, int y);

  public:
    explicit Application(const std::string &title, int width, int height);
    virtual ~Application();
    Application(const Application& cpy) = delete;
    Application& operator=(const Application& cpy) = delete;

    virtual bool OnCreate() = 0;

    virtual bool OnUpdate(float delta) = 0;

    virtual void OnKeyPressed(Key key) {}
    virtual void OnResize(int w, int h) {}

    void Run();

    inline static Application *Instance() { return _instance; }

    void DrawRectangle(const Graphics::Rectangle& rectangle = Graphics::Rectangle{}) const;

    void DrawText(const Graphics::Text& text) const;

    void DrawButton(Graphics::Button& button);

  };
}

