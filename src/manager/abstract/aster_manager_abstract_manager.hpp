#pragma once

#ifndef _ASTER_MANAGER_ABSTRACT_MANAGER_
#define _ASTER_MANAGER_ABSTRACT_MANAGER_

#include <memory>
#include <string>
#include <unordered_map>

namespace aster {
namespace manager {
namespace abstract {

template <typename T>
class manager {
  std::unordered_map<std::string, std::shared_ptr<T>> mv_Resources;

 public:
  std::shared_ptr<T> mf_get_by_name(
      const std::string& pc_ResourceName) noexcept {
    const auto lc_Found{this->mv_Resources.find(pc_ResourceName)};

    if (lc_Found != this->mv_Resources.end()) {
      return lc_Found->second;
    }

    const std::shared_ptr<T> lc_ResourcePtr{
        this->vmf_load_from_file(pc_ResourceName)};

    if (!lc_ResourcePtr) {
      return nullptr;
    }

    const auto lc_Emplaced{
        this->mv_Resources.emplace(pc_ResourceName, lc_ResourcePtr)};

    if (!lc_Emplaced.second) {
      return nullptr;
    }

    return lc_Emplaced.first->second;
  }

 protected:
  virtual std::shared_ptr<T> vmf_load_from_file(
      const std::string& pc_ResourceName) noexcept = 0;
};

}  // namespace abstract
}  // namespace manager
}  // namespace aster

#endif  // !_ASTER_MANAGER_ABSTRACT_MANAGER_
