#pragma once

#ifndef _ASTER_ACTOR_SHIP_
#define _ASTER_ACTOR_SHIP_

#include <SFML/Graphics.hpp>

#include "aster_actor_eternal_actor.hpp"

namespace aster {
namespace actor {

class ship : public eternal_actor {
 public:
  explicit ship(const sf::Sprite& pc_Sprite) noexcept;

  virtual void mvf_inner_tick() noexcept override;

  sf::Vector2f mf_get_gun_position() const noexcept;

  void mf_set_position_braking(const bool pc_PositionBraking) noexcept;
  void mf_set_rotation_braking(const bool pc_RotationBraking) noexcept;

 private:
  sf::Vector2f mf_find_gun_position() const noexcept;

  bool mv_PositionBraking{false}, mv_RotationBraking{false};
  sf::Vector2f mv_GunPosition{};

  static constexpr float msc_BrakingK{10.0f};
};

}  // namespace actor
}  // namespace aster

#endif  // !_ASTER_ACTOR_SHIP_
