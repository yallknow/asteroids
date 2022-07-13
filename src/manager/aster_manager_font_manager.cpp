#include "aster_manager_font_manager.hpp"

std::shared_ptr<sf::Font> aster::manager::font_manager::vmf_load_from_file(
    const std::string& pc_ResourceName) noexcept {
  std::shared_ptr<sf::Font> lv_FontPtr{std::make_shared<sf::Font>()};

  if (!lv_FontPtr->loadFromFile(pc_ResourceName)) {
    return nullptr;
  }

  return lv_FontPtr;
}
