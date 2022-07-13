#pragma once

#ifndef _ASTER_TEXT_
#define _ASTER_TEXT_

#include <SFML/Graphics.hpp>
#include <string>

namespace aster {

class text {
 public:
  explicit text(const std::string& pc_Data, const sf::Font& pc_Font,
                const sf::Vector2f& pc_Position) noexcept;

  sf::Text& mf_get_text() noexcept;

 protected:
  std::string mv_Data;
  sf::Font mv_Font;
  sf::Text mv_Text;
};

}  // namespace aster

#endif  // !_ASTER_TEXT_
