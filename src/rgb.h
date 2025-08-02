//
// Created by khovakim on 7/31/25.
//

#ifndef   RGB_H
# define  RGB_H

# include <cstdint>

struct RGB
{
  enum color {
    Black = 0,
    White = 1,
    Red   = 2
  };
  std::uint8_t r { };
  std::uint8_t g { };
  std::uint8_t b { };
};

RGB getColor(const RGB::color color);

#endif // RGB_H
