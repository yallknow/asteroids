#include "aster_text.hpp"

aster::text::text(const std::string& pc_Data, const sf::Font& pc_Font,
                  const sf::Vector2f& pc_Position) noexcept
    : mv_Data{pc_Data},
      mv_Font{pc_Font},
      mv_Text{this->mv_Data, this->mv_Font} {
  this->mv_Text.setOrigin(this->mv_Text.getGlobalBounds().width / 2.0f,
                          this->mv_Text.getGlobalBounds().height / 2.0f);
  this->mv_Text.setPosition(pc_Position);
}

sf::Text& aster::text::mf_get_text() noexcept { return this->mv_Text; }
