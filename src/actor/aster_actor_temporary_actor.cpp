#include "aster_actor_temporary_actor.hpp"

aster::actor::temporary_actor::temporary_actor(
    const sf::Sprite& pc_Sprite) noexcept
    : actor{pc_Sprite} {}

void aster::actor::temporary_actor::mvf_inner_tick() noexcept {
  if (!this->mv_IsVisible) {
    return;
  }

  const sf::Vector2f lc_OldPosition{this->mf_get_sprite().getPosition()};

  if (lc_OldPosition.x < msv_MinPosition.x - this->mv_TextureSize.x ||
      lc_OldPosition.x > msv_MaxPosition.x + this->mv_TextureSize.x ||
      lc_OldPosition.y < msv_MinPosition.y - this->mv_TextureSize.y ||
      lc_OldPosition.y > msv_MaxPosition.y + this->mv_TextureSize.y) {
    this->mv_IsVisible = false;
  }
}

void aster::actor::temporary_actor::mf_set_visible(
    const bool pc_IsVisible) noexcept {
  this->mv_IsVisible = pc_IsVisible;
}

bool aster::actor::temporary_actor::mf_is_visible() const noexcept {
  return this->mv_IsVisible;
}
