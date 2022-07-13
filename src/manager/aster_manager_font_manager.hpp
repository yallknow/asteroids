#pragma once

#ifndef _ASTER_MANAGER_FONT_MANAGER_
#define _ASTER_MANAGER_FONT_MANAGER_

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "abstract/aster_manager_abstract_manager.hpp"

namespace aster {
namespace manager {

class font_manager : public abstract::manager<sf::Font> {
 protected:
  std::shared_ptr<sf::Font> vmf_load_from_file(
      const std::string& pc_ResourceName) noexcept override;
};

}  // namespace manager
}  // namespace aster

#endif  // !_ASTER_MANAGER_FONT_MANAGER_
