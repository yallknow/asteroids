#pragma once

#ifndef _ASTER_ACTOR_TEMPORARY_ACTOR_
#define _ASTER_ACTOR_TEMPORARY_ACTOR_

#include <SFML/Graphics.hpp>

#include "abstract/aster_actor_abstract_actor.hpp"

namespace aster {
namespace actor {

class temporary_actor : public abstract::actor {
 public:
  explicit temporary_actor(const sf::Sprite& pc_Sprite) noexcept;

  virtual void mvf_inner_tick() noexcept override;

  void mf_set_visible(const bool pc_IsVisible) noexcept;
  bool mf_is_visible() const noexcept;

 private:
  bool mv_IsVisible{true};
};

}  // namespace actor
}  // namespace aster

#endif  // !_ASTER_ACTOR_TEMPORARY_ACTOR_
