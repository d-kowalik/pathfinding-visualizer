#include <glad/glad.h>

#include "../Util/Callback.hpp"

#include <GLFW/glfw3.h>

#include <string>
#include <functional>
#include <Input/Keycodes.hpp>

namespace sge {
  class Window {
  public:
    using OnMouseClickEvent = std::function<void(float, float)>;
    using OnResizeEvent = std::function<void(int, int)>;
    Util::Callback<float, float> OnMouseClick;
    Util::Callback<int, int> OnResize;
    Util::Callback<Key> OnButtonPressed;

  private:
    static Window* _instance;
    unsigned _last_fps = 0;

    GLFWwindow *_window;
    int _width, _height;
    std::string _title;

    void Resize(int w, int h);

    bool InitializeGLFW();

    bool CreateWindow();

    bool InitializeOpenGL();

    Window(int width, int height, std::string title);

  public:
    inline bool ShouldClose() const { return glfwWindowShouldClose(_window); }

    void Update() const;

    void Clear() const;

    void Close() const;

    inline int GetWidth() const { return _width; }
    inline int GetHeight() const { return _height; }

    GLFWwindow* GetNativeHandle() const { return _window; }

    static Window* Instance() { return _instance; }

    static Window* Create(int width, int height, const std::string& title);
    static void Destroy();

    friend void framebuffer_size_callback(GLFWwindow *window, int w, int h);

    void UpdateTitle(unsigned int fps);
  };
} // namespace sge