#include "aster_actor_ship.hpp"

#include "../aster_math.hpp"

aster::actor::ship::ship(const sf::Sprite& pc_Sprite) noexcept
    : eternal_actor{pc_Sprite} {
  this->mv_GunPosition = this->mf_find_gun_position();
}

void aster::actor::ship::mvf_inner_tick() noexcept {
  eternal_actor::mvf_inner_tick();

  this->mv_GunPosition = this->mf_find_gun_position();

  if (this->mv_PositionBraking) {
    this->mv_XDelta -= this->mv_XDelta / msc_BrakingK;
    this->mv_YDelta -= this->mv_YDelta / msc_BrakingK;
  }

  if (this->mv_RotationBraking) {
    this->mv_RotationDelta -= this->mv_RotationDelta / msc_BrakingK;
  }
}

sf::Vector2f aster::actor::ship::mf_get_gun_position() const noexcept {
  return this->mv_GunPosition;
}

void aster::actor::ship::mf_set_position_braking(
    const bool pc_PositionBraking) noexcept {
  this->mv_PositionBraking = pc_PositionBraking;
}

void aster::actor::ship::mf_set_rotation_braking(
    const bool pc_RotationBraking) noexcept {
  this->mv_RotationBraking = pc_RotationBraking;
}

sf::Vector2f aster::actor::ship::mf_find_gun_position() const noexcept {
  sf::Vector2f lv_GunPosition{this->mv_Sprite.getPosition()};

  lv_GunPosition.x += static_cast<float>(
      this->mv_TextureSize.x / 2.0f *
      std::sinf(f_deg_to_rad(this->mv_Sprite.getRotation())));

  lv_GunPosition.y -= static_cast<float>(
      this->mv_TextureSize.y / 2.0f *
      std::cosf(f_deg_to_rad(this->mv_Sprite.getRotation())));

  return lv_GunPosition;
}
