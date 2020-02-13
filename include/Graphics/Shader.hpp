#pragma once

#include "../Engine.hpp"

namespace sge::Graphics {
  class Shader {
    unsigned _type, _id;

  public:
    Shader(unsigned type, const std::string &data);
    ~Shader();

    unsigned GetId() const { return _id; }

    static Ref<Shader> CreateFromPath(unsigned type, const std::string& path);
    static Ref<Shader> CreateFromRawData(unsigned type, const std::string& data);

    void Delete() const;

  private:
    void Create(const std::string& data);
  };

}
