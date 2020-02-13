#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

#include <map>
#include <string>

namespace sge::Graphics {
  class Font {
  public:
    struct Character {
      unsigned texture_id;
      glm::ivec2 size;
      glm::ivec2 bearing;
      unsigned advance;
    };

  private:
    FT_Face _face;
    int _size;
    std::map<char, Character> _characters;

  public:
    Font(const std::string& path, int size, FT_Library ft);

    const std::map<char, Character>& GetCharacters() const { return _characters; }
    const int GetSize() const { return _size; }
  };
}