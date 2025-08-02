//
// Created by khovakim on 8/2/25.
//

#include "rgb.h"

RGB getColor(const RGB::color color)
{
  switch (color) {
    case RGB::Black: return RGB{0, 0, 0};
    case RGB::White: return RGB{255, 255, 255};
    case RGB::Red:   return RGB{255, 0, 0};
  }
  return RGB{0, 0, 0};
}