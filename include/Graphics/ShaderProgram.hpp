#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Engine.hpp"

namespace sge::Graphics {
  class ShaderProgram {
    unsigned _id;
    std::vector<Ref<Shader>> _shaders{};

  public:
    ShaderProgram(const std::vector<Ref<Shader>>& shaders);

    void Use() const;

    void SetUniform3f(const std::string& name, const glm::vec3 value) const;
    void SetUniformMat4f(const std::string& name, const glm::mat4& value) const;
  };
}