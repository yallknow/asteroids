#pragma once

#ifndef _ASTER_GAME_
#define _ASTER_GAME_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "aster_score.hpp"
#include "aster_text.hpp"

// _actors_include_
#include "actor/aster_actor_ship.hpp"
#include "actor/aster_actor_temporary_actor.hpp"
// !_actors_include_

// _managers_include_
#include "manager/aster_manager_font_manager.hpp"
#include "manager/aster_manager_music_manager.hpp"
#include "manager/aster_manager_sound_buffer_manager.hpp"
#include "manager/aster_manager_texture_manager.hpp"
// !_managers_include_

namespace aster {

class game {
  // _managers_
  static manager::font_manager msv_FontManager;
  static manager::music_manager msv_MusicManager;
  static manager::sound_buffer_manager msv_SoundBufferManager;
  static manager::texture_manager msv_TextureManager;
  // !_managers_

  // _font_paths_
  static const std::string msc_ScoreFontPath;
  // !_font_paths_

  // _music_paths_
  static const std::string msc_BackgroundMusicPath;
  // !_music_paths_

  // _sound_buffer_paths_
  static const std::string msc_BigCrashSoundBufferPath;
  static const std::string msc_DeathSoundBufferPath;
  static const std::string msc_ShotSoundBufferPath;
  static const std::string msc_SmallCrashSoundBufferPath;
  // !_sound_buffer_paths_

  // _sounds_
  sf::Sound mv_BigCrashSound{};
  sf::Sound mv_DeathSound{};
  sf::Sound mv_ShotSound{};
  sf::Sound mv_SmallCrashSound{};
  // !_sounds_

  // _texture_paths_
  static const std::string msc_BigAsteroidTexturePath;
  static const std::string msc_BulletTexturePath;
  static const std::string msc_ShipTexturePath;
  static const std::string msc_SmallAsteroidTexturePath;
  // !_texture_paths_

  // _inner_loading_
  template <typename T>
  static bool msf_load(
      manager::abstract::manager<T>& pc_Manager,
      const std::vector<std::string_view>& pc_ResourcePaths) noexcept {
    for (const std::string_view lc_ResourcePath : pc_ResourcePaths) {
      if (!pc_Manager.mf_get_by_name(lc_ResourcePath.data())) {
        return false;
      }
    }

    return true;
  }
  // !_inner_loading_

 public:
  // _loading_
  static bool msf_load_game() noexcept;
  // !_loading_

 private:
  //_uninitialized_members_
  text mv_EndGameText;
  score mv_Score;
  std::unique_ptr<actor::ship> mv_ShipPtr;
  sf::RenderWindow mv_Window;
  // !_uninitialized_members_

  // _window_settings_
  static const std::string msc_WindowTitle;

  static constexpr std::uint32_t msc_WindowWidth{800u};
  static constexpr std::uint32_t msc_WindowHeight{450u};
  static constexpr std::uint32_t msc_WindowFramerateLimit{60u};

  static const sf::Vector2f msc_WindowStartPosition;
  static const sf::Vector2f msc_WindowEndPosition;
  // !_window_settings_

 public:
  // _starting_
  game() noexcept;
  bool mf_start() noexcept;
  //  !_starting_

 private:
  // _game_over_flag_
  bool mv_IsGameOver{false};
  // ! _game_over_flag_

  // _actors_
  std::vector<actor::temporary_actor> mv_Bullets{};

  std::vector<actor::temporary_actor> mv_BigAsteroids{};
  std::vector<actor::temporary_actor> mv_SmallAsteroids{};

  static constexpr std::uint32_t msc_BigAsteroidsMaxCount{10u};
  static constexpr std::uint32_t msc_SmallAsteroidsMaxCount{5u};
  static constexpr std::uint32_t msc_SmallAsteroidsFromBigCount{2u};
  // !_actors_

  // _actors_settings_
  static constexpr float msc_BulletSpeed{7.0f};
  static constexpr float msc_ShipSpeed{3.0f};

  static constexpr float msc_ShipMaxRotation{10.0f};
  static constexpr float msc_ShipRotationIncrement{3.5f};

  static constexpr std::uint32_t msc_BigAsteroidPoints{100u};
  static constexpr std::uint32_t msc_SmallAsteroidPoints{50u};
  // !_actors_settings_

  // _random_
  static std::mt19937 msv_MT;

  static std::uniform_real_distribution<float> msc_XPositionRange;
  static std::uniform_real_distribution<float> msc_YPositionRange;

  static std::uniform_real_distribution<float> msc_XPositionDeltaRange;
  static std::uniform_real_distribution<float> msc_YPositionDeltaRange;
  static std::uniform_real_distribution<float> msc_RotationDeltaRange;
  // !_random_

  // _actors_control_
  void mf_add_temporary() noexcept;
  void mf_add_bullet() noexcept;
  void mf_add_asteroid(const bool pc_IsBig = true,
                       sf::Vector2f pv_Position = sf::Vector2f{-1.0f,
                                                               -1.0f}) noexcept;

  void mf_clear_damaged() noexcept;
  void mf_clear_temporary() noexcept;
  void mf_clear_temporary_actors(
      std::vector<actor::temporary_actor>& pv_Actors) noexcept;
  // !_actors_control_

  // _actions_for_all
  void mf_draw_all() noexcept;
  void mf_draw_temporary_actors(
      std::vector<actor::temporary_actor>& pv_Actors) noexcept;

  void mf_tick_all() noexcept;
  void mf_tick_temporary_actors(
      std::vector<actor::temporary_actor>& pv_Actors) noexcept;
  // !_actions_for_all

  // _key_controls_
  void mf_keys_pressed_handler(const sf::Keyboard::Key& pc_Key) noexcept;
  void mf_keys_released_handler(const sf::Keyboard::Key& pc_Key) noexcept;
  // !_key_controls_

  // _ship_control_
  void mf_check_ship() noexcept;
  // !_ship_control_
};

}  // namespace aster

#endif  // !_ASTER_GAME_
