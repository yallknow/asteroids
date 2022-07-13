#pragma once

#ifndef _ASTER_MANAGER_SOUND_BUFFER_MANAGER_
#define _ASTER_MANAGER_SOUND_BUFFER_MANAGER_

#include <SFML/Audio.hpp>
#include <memory>
#include <string>

#include "abstract/aster_manager_abstract_manager.hpp"

namespace aster {
namespace manager {

class sound_buffer_manager : public abstract::manager<sf::SoundBuffer> {
 protected:
  std::shared_ptr<sf::SoundBuffer> vmf_load_from_file(
      const std::string& pc_ResourceName) noexcept override;
};

}  // namespace manager
}  // namespace aster

#endif  // !_ASTER_MANAGER_SOUND_BUFFER_MANAGER_
