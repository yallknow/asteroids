#include "aster_manager_texture_manager.hpp"

std::shared_ptr<sf::Texture>
aster::manager::texture_manager::vmf_load_from_file(
    const std::string& pc_ResourceName) noexcept {
  sf::Image lv_Image{};

  if (!lv_Image.loadFromFile(pc_ResourceName)) {
    return nullptr;
  }

  std::shared_ptr<sf::Texture> lv_TexturePtr{std::make_shared<sf::Texture>()};

  if (!lv_TexturePtr->loadFromImage(lv_Image)) {
    return nullptr;
  }

  return lv_TexturePtr;
}
