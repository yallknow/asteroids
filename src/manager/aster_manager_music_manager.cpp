#include "aster_manager_music_manager.hpp"

std::shared_ptr<sf::Music> aster::manager::music_manager::vmf_load_from_file(
    const std::string& pc_ResourceName) noexcept {
  std::shared_ptr<sf::Music> lv_MusicPtr{std::make_shared<sf::Music>()};

  if (!lv_MusicPtr->openFromFile(pc_ResourceName)) {
    return nullptr;
  }

  return lv_MusicPtr;
}
