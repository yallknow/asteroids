#pragma once

#ifndef _ASTER_SCORE_
#define _ASTER_SCORE_

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <string>

#include "aster_text.hpp"

namespace aster {

class score : public text {
 public:
  explicit score(const std::string& pc_Data, const sf::Font& pc_Font,
                 const sf::Vector2f& pc_Position) noexcept;

  void mf_add(const std::uint64_t& pc_Value) noexcept;

 private:
  std::uint64_t mv_ScoreValue{};
};

}  // namespace aster

#endif  // !_ASTER_SCORE_
