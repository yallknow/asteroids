#include "aster_score.hpp"

aster::score::score(const std::string& pc_Data, const sf::Font& pc_Font,
                    const sf::Vector2f& pc_Position) noexcept
    : text{pc_Data, pc_Font, pc_Position} {
  this->mv_Text = sf::Text{this->mv_Data + std::to_string(this->mv_ScoreValue),
                           this->mv_Font};
}

void aster::score::mf_add(const std::uint64_t& pc_Value) noexcept {
  this->mv_ScoreValue += pc_Value;
  this->mv_Text = sf::Text{this->mv_Data + std::to_string(this->mv_ScoreValue),
                           this->mv_Font};
}
