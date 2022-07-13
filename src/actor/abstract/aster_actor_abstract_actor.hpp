#pragma once

#ifndef _ASTER_ACTOR_ABSTRACT_ACTOR_
#define _ASTER_ACTOR_ABSTRACT_ACTOR_

#include <SFML/Graphics.hpp>

namespace aster {
namespace actor {
namespace abstract {

class actor {
 protected:
  sf::Sprite mv_Sprite;
  sf::Vector2u mv_TextureSize;

  float mv_XDelta{}, mv_YDelta{}, mv_RotationDelta{};

  static sf::Vector2f msv_MinPosition, msv_MaxPosition;

 public:
  explicit actor(const sf::Sprite& pc_Sprite) noexcept;

  void mvf_tick() noexcept;

  sf::Sprite& mf_get_sprite() noexcept;
  sf::Vector2u mf_get_texture_size() const noexcept;

  float mf_get_x_delta() const noexcept;
  float mf_get_y_delta() const noexcept;
  float mf_get_rotation_delta() const noexcept;

  void mf_set_x_delta(const float pc_XDelta) noexcept;
  void mf_set_y_delta(const float pc_YDelta) noexcept;
  void mf_set_rotation_delta(const float pc_RotationDelta) noexcept;

  static void msf_set_min_position(const sf::Vector2f& pc_MinPosition) noexcept;
  static void msf_set_max_position(const sf::Vector2f& pc_MaxPosition) noexcept;

 protected:
  virtual void mvf_inner_tick() noexcept = 0;
};

}  // namespace abstract
}  // namespace actor
}  // namespace aster

#endif  // !_ASTER_ACTOR_ABSTRACT_ACTOR_
