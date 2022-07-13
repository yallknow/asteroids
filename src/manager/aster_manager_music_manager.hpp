#pragma once

#ifndef _ASTER_MANAGER_MUSIC_MANAGER_
#define _ASTER_MANAGER_MUSIC_MANAGER_

#include <SFML/Audio.hpp>
#include <memory>
#include <string>

#include "abstract/aster_manager_abstract_manager.hpp"

namespace aster {
namespace manager {

class music_manager : public abstract::manager<sf::Music> {
 protected:
  std::shared_ptr<sf::Music> vmf_load_from_file(
      const std::string& pc_ResourceName) noexcept override;
};

}  // namespace manager
}  // namespace aster

#endif  // !_ASTER_MANAGER_MUSIC_MANAGER_
