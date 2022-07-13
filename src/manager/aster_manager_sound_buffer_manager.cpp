#include "aster_manager_sound_buffer_manager.hpp"

std::shared_ptr<sf::SoundBuffer>
aster::manager::sound_buffer_manager::vmf_load_from_file(
    const std::string& pc_ResourceName) noexcept {
  std::shared_ptr<sf::SoundBuffer> lv_SoundBufferPtr{
      std::make_shared<sf::SoundBuffer>()};

  if (!lv_SoundBufferPtr->loadFromFile(pc_ResourceName)) {
    return nullptr;
  }

  return lv_SoundBufferPtr;
}
