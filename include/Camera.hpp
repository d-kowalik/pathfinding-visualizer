#pragma once

#include <glm/glm.hpp>

namespace sge {
  class Camera {

    glm::vec3 _position = glm::vec3(.0f, .0f, 3.0f);
    glm::vec3 _front = glm::vec3(.0f, .0f, -1.f);
    glm::vec3 _up = glm::vec3(.0f, 1.0f, .0f);
    glm::vec3 _right;
    float _speed;

  public:
    enum class Direction {
      LEFT, RIGHT, UP, DOWN
    };

    explicit Camera(float speed) noexcept;
    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float speed);

    glm::mat4 View() const;
    void Move(Direction direciton, float delta);

  private:
    void Update();
  };
}



