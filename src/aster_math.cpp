#include "aster_math.hpp"

float aster::f_deg_to_rad(const float& pc_Degrees) {
  return pc_Degrees / _ASTER_RAD_ * _ASTER_PI_;
}
