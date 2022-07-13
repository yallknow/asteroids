#include "aster_game.hpp"

#include <algorithm>
#include <string_view>

#include "actor/abstract/aster_actor_abstract_actor.hpp"
#include "aster_math.hpp"

// _managers_
aster::manager::font_manager aster::game::msv_FontManager{};
aster::manager::music_manager aster::game::msv_MusicManager{};
aster::manager::sound_buffer_manager aster::game::msv_SoundBufferManager{};
aster::manager::texture_manager aster::game::msv_TextureManager{};
// !_managers_

// _font_paths_
const std::string aster::game::msc_ScoreFontPath{"font/score_font.ttf"};
// !_font_paths_

// _music_paths_
const std::string aster::game::msc_BackgroundMusicPath{
    "music/background_music.ogg"};
// !_music_paths_

// _sound_buffer_paths_
const std::string aster::game::msc_BigCrashSoundBufferPath{
    "sound/big_crash_sound_buffer.ogg"};
const std::string aster::game::msc_DeathSoundBufferPath{
    "sound/death_sound_buffer.ogg"};
const std::string aster::game::msc_ShotSoundBufferPath{
    "sound/shot_sound_buffer.ogg"};
const std::string aster::game::msc_SmallCrashSoundBufferPath{
    "sound/small_crash_sound_buffer.ogg"};
// !_sound_buffer_paths_

// _texture_paths_
const std::string aster::game::msc_BigAsteroidTexturePath{
    "texture/big_asteroid_texture.png"};
const std::string aster::game::msc_BulletTexturePath{
    "texture/bullet_texture.png"};
const std::string aster::game::msc_ShipTexturePath{"texture/ship_texture.png"};
const std::string aster::game::msc_SmallAsteroidTexturePath{
    "texture/small_asteroid_texture.png"};
// !_texture_paths_

// _loading_
bool aster::game::msf_load_game() noexcept {
  return msf_load<sf::Font>(msv_FontManager, {msc_ScoreFontPath}) &&
         msf_load<sf::Music>(msv_MusicManager, {msc_BackgroundMusicPath}) &&
         msf_load<sf::SoundBuffer>(
             msv_SoundBufferManager,
             {msc_BigCrashSoundBufferPath, msc_DeathSoundBufferPath,
              msc_ShotSoundBufferPath, msc_SmallCrashSoundBufferPath}) &&
         msf_load<sf::Texture>(
             msv_TextureManager,
             {msc_BigAsteroidTexturePath, msc_BulletTexturePath,
              msc_ShipTexturePath, msc_SmallAsteroidTexturePath});
}
// !_loading_

// _window_settings_
const std::string aster::game::msc_WindowTitle{"Asteroids"};

const sf::Vector2f aster::game::msc_WindowStartPosition{0.0f, 0.0f};
const sf::Vector2f aster::game::msc_WindowEndPosition{
    static_cast<float>(msc_WindowWidth), static_cast<float>(msc_WindowHeight)};
// !_window_settings_

// _starting_
aster::game::game() noexcept
    : mv_EndGameText{"Press \"Enter\" to start a new game.",
                     *msv_FontManager.mf_get_by_name(msc_ScoreFontPath),
                     sf::Vector2f{msc_WindowWidth / 2.0f,
                                  msc_WindowHeight / 2.0f}},
      mv_Score{"Score: ", *msv_FontManager.mf_get_by_name(msc_ScoreFontPath),
               sf::Vector2f{0.0f, 0.0f}},
      mv_ShipPtr{std::make_unique<actor::ship>(
          sf::Sprite{*msv_TextureManager.mf_get_by_name(msc_ShipTexturePath)})},
      mv_Window{sf::VideoMode{msc_WindowWidth, msc_WindowHeight},
                msc_WindowTitle} {
  this->mv_BigCrashSound.setBuffer(
      *msv_SoundBufferManager.mf_get_by_name(msc_BigCrashSoundBufferPath));
  this->mv_DeathSound.setBuffer(
      *msv_SoundBufferManager.mf_get_by_name(msc_DeathSoundBufferPath));
  this->mv_ShotSound.setBuffer(
      *msv_SoundBufferManager.mf_get_by_name(msc_ShotSoundBufferPath));
  this->mv_SmallCrashSound.setBuffer(
      *msv_SoundBufferManager.mf_get_by_name(msc_SmallCrashSoundBufferPath));

  this->mv_ShipPtr->mf_get_sprite().setPosition(msc_WindowWidth / 2.0f,
                                                msc_WindowHeight / 2.0f);

  this->mv_Window.setFramerateLimit(msc_WindowFramerateLimit);

  actor::abstract::actor::msf_set_min_position(msc_WindowStartPosition);
  actor::abstract::actor::msf_set_max_position(msc_WindowEndPosition);

  this->mf_add_temporary();
}

bool aster::game::mf_start() noexcept {
  const std::shared_ptr<sf::Music> lc_BackgroundMusicPtr{
      msv_MusicManager.mf_get_by_name(msc_BackgroundMusicPath)};

  lc_BackgroundMusicPtr->setLoop(true);
  lc_BackgroundMusicPtr->play();

  while (this->mv_Window.isOpen()) {
    sf::Event lv_Event{};

    if (this->mv_Window.pollEvent(lv_Event)) {
      switch (lv_Event.type) {
        case sf::Event::Closed: {
          this->mv_Window.close();
          return true;
        }
        case sf::Event::MouseButtonPressed: {
          this->mf_add_bullet();
          break;
        }
        case sf::Event::KeyPressed: {
          if (this->mv_IsGameOver && lv_Event.key.code == sf::Keyboard::Enter) {
            return false;
          }

          this->mf_keys_pressed_handler(lv_Event.key.code);
          break;
        }
        case sf::Event::KeyReleased: {
          this->mf_keys_released_handler(lv_Event.key.code);
          break;
        }
      }
    }

    this->mv_Window.clear();
    this->mf_draw_all();
    this->mv_Window.display();

    if (!this->mv_IsGameOver) {
      this->mf_tick_all();

      this->mf_clear_damaged();
      this->mf_clear_temporary();
      this->mf_add_temporary();

      this->mf_check_ship();
    }
  }

  return true;
}
// !_starting_

// _random_
std::mt19937 aster::game::msv_MT{std::random_device{}()};

std::uniform_real_distribution<float> aster::game::msc_XPositionRange{
    msc_WindowStartPosition.x, msc_WindowEndPosition.x};
std::uniform_real_distribution<float> aster::game::msc_YPositionRange{
    msc_WindowStartPosition.y, msc_WindowEndPosition.y};

std::uniform_real_distribution<float> aster::game::msc_XPositionDeltaRange{
    0.5f, 1.5f};
std::uniform_real_distribution<float> aster::game::msc_YPositionDeltaRange{
    0.5f, 1.5f};
std::uniform_real_distribution<float> aster::game::msc_RotationDeltaRange{
    -10.0f, 10.0f};
// !_random_

// _actors_control_
void aster::game::mf_add_temporary() noexcept {
  while (this->mv_BigAsteroids.size() < msc_BigAsteroidsMaxCount) {
    this->mf_add_asteroid(true);
  }

  while (this->mv_SmallAsteroids.size() < msc_SmallAsteroidsMaxCount) {
    this->mf_add_asteroid(false);
  }
}

void aster::game::mf_add_bullet() noexcept {
  if (this->mv_ShotSound.getStatus() == sf::SoundSource::Status::Playing) {
    return;
  }

  this->mv_Bullets.emplace_back(
      sf::Sprite{*msv_TextureManager.mf_get_by_name(msc_BulletTexturePath)});

  actor::temporary_actor& lv_BulletLink{this->mv_Bullets.back()};

  lv_BulletLink.mf_get_sprite().setPosition(
      this->mv_ShipPtr->mf_get_gun_position());
  lv_BulletLink.mf_get_sprite().setRotation(
      this->mv_ShipPtr->mf_get_sprite().getRotation());

  lv_BulletLink.mf_set_x_delta(
      msc_BulletSpeed *
      std::sinf(f_deg_to_rad(lv_BulletLink.mf_get_sprite().getRotation())));
  lv_BulletLink.mf_set_y_delta(
      -msc_BulletSpeed *
      std::cosf(f_deg_to_rad(lv_BulletLink.mf_get_sprite().getRotation())));

  this->mv_ShotSound.play();
}

void aster::game::mf_add_asteroid(const bool pc_IsBig,
                                  sf::Vector2f pv_Position) noexcept {
  std::shared_ptr<sf::Texture> lv_TexturePtr{nullptr};

  if (pc_IsBig) {
    lv_TexturePtr =
        msv_TextureManager.mf_get_by_name(msc_BigAsteroidTexturePath);
  } else {
    lv_TexturePtr =
        msv_TextureManager.mf_get_by_name(msc_SmallAsteroidTexturePath);
  }

  actor::temporary_actor lv_Asteroid{sf::Sprite{*lv_TexturePtr}};

  const float lc_XDelta{msv_MT() % 2 ? msc_XPositionDeltaRange(msv_MT)
                                     : -msc_XPositionDeltaRange(msv_MT)};
  const float lc_YDelta{msv_MT() % 2 ? msc_YPositionDeltaRange(msv_MT)
                                     : -msc_YPositionDeltaRange(msv_MT)};

  if (pv_Position == sf::Vector2f{-1.0f, -1.0f}) {
    // Positioning of a new asteroid in accordance with its direction
    if (msv_MT() % 2) {
      if (lc_XDelta > 0) {
        pv_Position.x = msc_WindowStartPosition.x;
      } else {
        pv_Position.x = msc_WindowEndPosition.x;
      }

      pv_Position.y = msc_YPositionRange(msv_MT);
    } else {
      if (lc_YDelta > 0) {
        pv_Position.y = msc_WindowStartPosition.y;
      } else {
        pv_Position.y = msc_WindowEndPosition.y;
      }

      pv_Position.x = msc_XPositionRange(msv_MT);
    }
  }

  lv_Asteroid.mf_get_sprite().setPosition(pv_Position);

  lv_Asteroid.mf_set_x_delta(lc_XDelta);
  lv_Asteroid.mf_set_y_delta(lc_YDelta);
  lv_Asteroid.mf_set_rotation_delta(msc_RotationDeltaRange(msv_MT));

  if (pc_IsBig) {
    this->mv_BigAsteroids.emplace_back(lv_Asteroid);
  } else {
    this->mv_SmallAsteroids.emplace_back(lv_Asteroid);
  }
}

void aster::game::mf_clear_damaged() noexcept {
  for (actor::temporary_actor& lv_Bullet : this->mv_Bullets) {
    auto lv_Found{std::find_if(
        this->mv_BigAsteroids.begin(), this->mv_BigAsteroids.end(),
        [&lv_Bullet](actor::temporary_actor& pv_BigAsteroid) -> bool {
          return lv_Bullet.mf_get_sprite().getGlobalBounds().intersects(
              pv_BigAsteroid.mf_get_sprite().getGlobalBounds());
        })};

    if (lv_Found != this->mv_BigAsteroids.end()) {
      for (std::uint64_t i{}; i < msc_SmallAsteroidsFromBigCount; ++i) {
        this->mf_add_asteroid(false, lv_Found->mf_get_sprite().getPosition());
      }

      lv_Found->mf_set_visible(false);
      lv_Bullet.mf_set_visible(false);

      this->mv_Score.mf_add(msc_BigAsteroidPoints);
      this->mv_BigCrashSound.play();
      continue;
    }

    auto lv_BorderToDelete{std::remove_if(
        this->mv_SmallAsteroids.begin(), this->mv_SmallAsteroids.end(),
        [&lv_Bullet](actor::temporary_actor& pv_SmallAsteroid) -> bool {
          return lv_Bullet.mf_get_sprite().getGlobalBounds().intersects(
              pv_SmallAsteroid.mf_get_sprite().getGlobalBounds());
        })};

    this->mv_Score.mf_add(
        msc_SmallAsteroidPoints *
        std::distance(lv_BorderToDelete, this->mv_SmallAsteroids.end()));

    if (lv_BorderToDelete != this->mv_SmallAsteroids.end()) {
      this->mv_SmallAsteroids.erase(lv_BorderToDelete,
                                    this->mv_SmallAsteroids.end());

      this->mv_SmallCrashSound.play();
    }
  }
}

void aster::game::mf_clear_temporary() noexcept {
  this->mf_clear_temporary_actors(this->mv_Bullets);
  this->mf_clear_temporary_actors(this->mv_BigAsteroids);
  this->mf_clear_temporary_actors(this->mv_SmallAsteroids);
}

void aster::game::mf_clear_temporary_actors(
    std::vector<actor::temporary_actor>& pv_Actors) noexcept {
  pv_Actors.erase(
      std::remove_if(pv_Actors.begin(), pv_Actors.end(),
                     [](const actor::temporary_actor& pc_Current) -> bool {
                       return !pc_Current.mf_is_visible();
                     }),
      pv_Actors.end());
}
// !_actors_control_

// _actions_for_all
void aster::game::mf_draw_all() noexcept {
  this->mv_Window.draw(this->mv_Score.mf_get_text());

  if (this->mv_IsGameOver) {
    this->mv_Window.draw(this->mv_EndGameText.mf_get_text());
  }

  this->mv_Window.draw(this->mv_ShipPtr->mf_get_sprite());

  this->mf_draw_temporary_actors(this->mv_Bullets);
  this->mf_draw_temporary_actors(this->mv_BigAsteroids);
  this->mf_draw_temporary_actors(this->mv_SmallAsteroids);
}

void aster::game::mf_draw_temporary_actors(
    std::vector<actor::temporary_actor>& pv_Actors) noexcept {
  for (actor::temporary_actor& lv_Actor : pv_Actors) {
    this->mv_Window.draw(lv_Actor.mf_get_sprite());
  }
}

void aster::game::mf_tick_all() noexcept {
  this->mv_ShipPtr->mvf_tick();

  this->mf_tick_temporary_actors(this->mv_Bullets);
  this->mf_tick_temporary_actors(this->mv_BigAsteroids);
  this->mf_tick_temporary_actors(this->mv_SmallAsteroids);
}

void aster::game::mf_tick_temporary_actors(
    std::vector<actor::temporary_actor>& pv_Actors) noexcept {
  for (actor::temporary_actor& lv_Actor : pv_Actors) {
    lv_Actor.mvf_tick();
  }
}
// !_actions_for_all

// _key_controls_
void aster::game::mf_keys_pressed_handler(
    const sf::Keyboard::Key& pc_Key) noexcept {
  switch (pc_Key) {
    case sf::Keyboard::W: {
      this->mv_ShipPtr->mf_set_x_delta(
          msc_ShipSpeed *
          std::sinf(
              f_deg_to_rad(this->mv_ShipPtr->mf_get_sprite().getRotation())));
      this->mv_ShipPtr->mf_set_y_delta(
          -msc_ShipSpeed *
          std::cosf(
              f_deg_to_rad(this->mv_ShipPtr->mf_get_sprite().getRotation())));

      this->mv_ShipPtr->mf_set_position_braking(false);
      break;
    }
    case sf::Keyboard::S: {
      this->mv_ShipPtr->mf_set_x_delta(
          -msc_ShipSpeed / 2.0f *
          std::sinf(
              f_deg_to_rad(this->mv_ShipPtr->mf_get_sprite().getRotation())));
      this->mv_ShipPtr->mf_set_y_delta(
          msc_ShipSpeed / 2.0f *
          std::cosf(
              f_deg_to_rad(this->mv_ShipPtr->mf_get_sprite().getRotation())));

      this->mv_ShipPtr->mf_set_position_braking(false);
      break;
    }
    case sf::Keyboard::A: {
      if (this->mv_ShipPtr->mf_get_rotation_delta() > -msc_ShipMaxRotation) {
        this->mv_ShipPtr->mf_set_rotation_delta(
            this->mv_ShipPtr->mf_get_rotation_delta() -
            msc_ShipRotationIncrement);
      }

      this->mv_ShipPtr->mf_set_rotation_braking(false);
      break;
    }
    case sf::Keyboard::D: {
      if (this->mv_ShipPtr->mf_get_rotation_delta() < msc_ShipMaxRotation) {
        this->mv_ShipPtr->mf_set_rotation_delta(
            this->mv_ShipPtr->mf_get_rotation_delta() +
            msc_ShipRotationIncrement);
      }

      this->mv_ShipPtr->mf_set_rotation_braking(false);
      break;
    }
  }
}

void aster::game::mf_keys_released_handler(
    const sf::Keyboard::Key& pc_Key) noexcept {
  switch (pc_Key) {
    case sf::Keyboard::W:
    case sf::Keyboard::S: {
      this->mv_ShipPtr->mf_set_position_braking(true);
      break;
    }
    case sf::Keyboard::A:
    case sf::Keyboard::D: {
      this->mv_ShipPtr->mf_set_rotation_braking(true);
      break;
    }
  }
}
// !_key_controls_

// _ship_control_
void aster::game::mf_check_ship() noexcept {
  const sf::Vector2f lc_ShipCenter{
      this->mv_ShipPtr->mf_get_sprite().getPosition()};

  auto lv_found{std::find_if(
      this->mv_BigAsteroids.begin(), this->mv_BigAsteroids.end(),
      [&lc_ShipCenter](actor::temporary_actor& pv_BigAsteroid) -> bool {
        return pv_BigAsteroid.mf_get_sprite().getGlobalBounds().contains(
            lc_ShipCenter);
      })};

  if (lv_found == this->mv_BigAsteroids.end()) {
    lv_found = std::find_if(
        this->mv_SmallAsteroids.begin(), this->mv_SmallAsteroids.end(),
        [&lc_ShipCenter](actor::temporary_actor& pv_SmallAsteroid) -> bool {
          return pv_SmallAsteroid.mf_get_sprite().getGlobalBounds().contains(
              lc_ShipCenter);
        });

    if (lv_found == this->mv_SmallAsteroids.end()) {
      return;
    }
  }

  this->mv_IsGameOver = true;
  this->mv_DeathSound.play();
}
// !_ship_control_
