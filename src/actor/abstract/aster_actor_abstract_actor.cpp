#include "aster_actor_abstract_actor.hpp"

sf::Vector2f aster::actor::abstract::actor::msv_MinPosition{};
sf::Vector2f aster::actor::abstract::actor::msv_MaxPosition{};

aster::actor::abstract::actor::actor(const sf::Sprite& pc_Sprite) noexcept
    : mv_Sprite{pc_Sprite},
      mv_TextureSize{this->mv_Sprite.getTexture()->getSize()} {
  this->mv_Sprite.setOrigin(this->mv_TextureSize.x / 2.0f,
                            this->mv_TextureSize.y / 2.0f);
}

void aster::actor::abstract::actor::mvf_tick() noexcept {
  const sf::Vector2f lc_OldPosition{this->mv_Sprite.getPosition()};

  this->mv_Sprite.setPosition(lc_OldPosition.x + this->mv_XDelta,
                              lc_OldPosition.y + this->mv_YDelta);

  this->mv_Sprite.setRotation(this->mv_Sprite.getRotation() +
                              this->mv_RotationDelta);

  this->mvf_inner_tick();
}

sf::Sprite& aster::actor::abstract::actor::mf_get_sprite() noexcept {
  return this->mv_Sprite;
}

sf::Vector2u aster::actor::abstract::actor::mf_get_texture_size()
    const noexcept {
  return this->mv_TextureSize;
}

float aster::actor::abstract::actor::mf_get_x_delta() const noexcept {
  return this->mv_XDelta;
}

float aster::actor::abstract::actor::mf_get_y_delta() const noexcept {
  return this->mv_YDelta;
}

float aster::actor::abstract::actor::mf_get_rotation_delta() const noexcept {
  return this->mv_RotationDelta;
}

void aster::actor::abstract::actor::mf_set_x_delta(
    const float pc_XDelta) noexcept {
  this->mv_XDelta = pc_XDelta;
}

void aster::actor::abstract::actor::mf_set_y_delta(
    const float pc_YDelta) noexcept {
  this->mv_YDelta = pc_YDelta;
}

void aster::actor::abstract::actor::mf_set_rotation_delta(
    const float pc_RotationDelta) noexcept {
  this->mv_RotationDelta = pc_RotationDelta;
}

void aster::actor::abstract::actor::msf_set_min_position(
    const sf::Vector2f& pc_MinPosition) noexcept {
  msv_MinPosition = pc_MinPosition;
}

void aster::actor::abstract::actor::msf_set_max_position(
    const sf::Vector2f& pc_MaxPosition) noexcept {
  msv_MaxPosition = pc_MaxPosition;
}
