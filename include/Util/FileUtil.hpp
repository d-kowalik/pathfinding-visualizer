#pragma once

#include <optional>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

namespace sge::FileUtil {

  std::optional<std::string> Read(const std::string &path) {
    printf("Reading file: %s\n", path.data());
    std::ifstream ifstream{path};
    if (ifstream.is_open()) {
      ifstream.unsetf(std::ios::skipws);
      std::string output{};
      std::copy(std::istream_iterator<char>(ifstream), std::istream_iterator<char>(), std::back_inserter(output));
      return output;
    }
    return {};
  }

}