#pragma once

#include <memory>
#include <string>

namespace sge {
  template<typename T>
  using Ref = std::shared_ptr<T>;

  template<typename T, typename...Args>
  Ref<T> MakeRef(Args... args) {
    return std::make_shared<T>(args...);
  }
}