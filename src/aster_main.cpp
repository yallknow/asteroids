#include "aster_game.hpp"

int main() {
  if (!aster::game::msf_load_game()) {
    return EXIT_FAILURE;
  }

  while (true) {
    aster::game lv_Game{};

    if (lv_Game.mf_start()) {
      break;
    }
  }

  return EXIT_SUCCESS;
}
