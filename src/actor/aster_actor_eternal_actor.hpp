#pragma once

#ifndef _ASTER_ACTOR_ETERNAL_ACTOR_
#define _ASTER_ACTOR_ETERNAL_ACTOR_

#include <SFML/Graphics.hpp>

#include "abstract/aster_actor_abstract_actor.hpp"

namespace aster {
namespace actor {

class eternal_actor : public abstract::actor {
 public:
  explicit eternal_actor(const sf::Sprite& pc_Sprite) noexcept;

  virtual void mvf_inner_tick() noexcept override;
};

}  // namespace actor
}  // namespace aster

#endif  // !_ASTER_ACTOR_ETERNAL_ACTOR_
