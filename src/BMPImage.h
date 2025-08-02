//
// Created by khovakim on 7/31/25.
//

#ifndef   BMPIMAGE_H
# define  BMPIMAGE_H

#include "image.h"

#include <cstdint> // For std::uint16_t, std::uint32_t
#include <fstream> // For std::ifstream
#include <string>  // For std::string
#include <vector>  // For std::vector

/// This class encapsulates all logic required to load, display, modify,
/// and save BMP images (specifically 24-bit or 32-bit BMPs).
/// It reads raw pixel data, prints the image to the console (black and white only),
/// draws a line (used to draw a cross), and saves the image.

struct RGB;
class  Point;

class BMPImage final : public Image
{
public:
  BMPImage() = default;
  ~BMPImage() override = default;

public:
  // Loads a BMP file from the given path.
  bool load(const std::string& filePath) override;

  // Saves the current image state to a new BMP file.
  [[nodiscard]] bool save(const std::string& filePath) const override;

  // Displays the image in the console using ASCII characters:
  // ' ' for black pixels (0,0,0), '█' for white pixels (255,255,255).
  void display() const override;

  // (Optional accessors if needed outside)
  [[nodiscard]] int getWidth()  const noexcept override { return m_width;  }
  [[nodiscard]] int getHeight() const noexcept override { return m_height; }

  // Draws an X-shaped cross from corners using drawLine.
  void drawCross();

  // return true if the point into the image
  [[nodiscard]] bool isInside(const Point& p) const noexcept;

private:
  // Internal helper to read and parse BMP headers.
  bool _readHeaders(std::ifstream& in);

  // Internal pixel drawing function to directly modify RGB values.
  void _drawPixel(const Point& p, const RGB& color);

  // Draws a line on the image using Bresenham’s algorithm.
  void _drawLine(const Point& start, const Point& end, const RGB& color);

private:

  // Image properties from the BMP headers.
  std::uint16_t m_bitCount   { };  // bits per pixel (should be 24 or 32)
  std::int32_t  m_width      { };  // image width in pixels
  std::int32_t  m_height     { };  // image height in pixels
  std::int32_t  m_rowStride  { };  // actual bytes per row (including padding)
  std::uint32_t m_dataOffset { };  // where pixel data starts (from file header)

  // We use #pragma pack to disable structure padding, ensuring these structures
  // match the exact byte layout used in BMP files.
#pragma pack(push, 1)
  struct BMPFileHeader {
    std::uint16_t bfType;      // Magic number: must be 'BM' (0x4D42)
    std::uint32_t bfSize;      // Size of the BMP file in bytes
    std::uint16_t bfReserved1; // Reserved; must be 0
    std::uint16_t bfReserved2; // Reserved; must be 0
    std::uint32_t bfOffBits;   // Offset to the start of the pixel data
  }; // 14 byte

  struct BMPInfoHeader {
    std::uint32_t biSize;            // Size of this header (40 bytes)
    std::int32_t  biWidth;           // Image width in pixels
    std::int32_t  biHeight;          // Image height in pixels (can be negative)
    std::uint16_t biPlanes;          // Number of color planes (must be 1)
    std::uint16_t biBitCount;        // Bits per pixel (should be 24 or 32)
    std::uint32_t biCompression;     // Compression type (should be 0 for no
                                     // compression)
    std::uint32_t biSizeImage;       // Image data size (can be 0 if uncompressed)
    std::int32_t  biXPixelsPerMeter; // Horizontal resolution (pixels per meter)
    std::int32_t  biYPixelsPerMeter; // Vertical resolution (pixels per meter)
    std::uint32_t biClrUsed;         // Number of colors used (0 = all)
    std::uint32_t biClrImportant;    // Number of important colors (0 = all)
  }; // 40 byte
#pragma pack(pop)

  BMPFileHeader m_fileHeader{}; // Instance of the file header
  BMPInfoHeader m_infoHeader{}; // Instance of the info header

  // Image pixel data stored in raw bytes (BGR format per BMP spec).
  std::vector<std::uint8_t> m_data;

};




#endif // BMPIMAGE_H
