#include "aster_actor_eternal_actor.hpp"

aster::actor::eternal_actor::eternal_actor(const sf::Sprite& pc_Sprite) noexcept
    : actor{pc_Sprite} {}

void aster::actor::eternal_actor::mvf_inner_tick() noexcept {
  const sf::Vector2f lc_OldPosition{this->mv_Sprite.getPosition()};

  if (lc_OldPosition.x < msv_MinPosition.x - this->mv_TextureSize.x) {
    this->mv_Sprite.setPosition(msv_MaxPosition.x, lc_OldPosition.y);
  }

  if (lc_OldPosition.x > msv_MaxPosition.x + this->mv_TextureSize.x) {
    this->mv_Sprite.setPosition(msv_MinPosition.x, lc_OldPosition.y);
  }

  if (lc_OldPosition.y < msv_MinPosition.y - this->mv_TextureSize.y) {
    this->mv_Sprite.setPosition(lc_OldPosition.x, msv_MaxPosition.y);
  }

  if (lc_OldPosition.y > msv_MaxPosition.y + this->mv_TextureSize.y) {
    this->mv_Sprite.setPosition(lc_OldPosition.x, msv_MinPosition.y);
  }
}
