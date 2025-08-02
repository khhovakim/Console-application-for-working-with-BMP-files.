//
// Created by khovakim on 7/31/25.
//

#include "BMPImage.h"

#include "point.h"

#include <fstream>  // For std::ifstream, std::ofstream
#include <iostream> // For std::cerr, std::cout
#include <cmath>    // For std::abs

#include "rgb.h"    // For RGB
#include "point.h"  // For Point

namespace {

constexpr int BMP_IMAGE_TYPE   { 0x4D42 };
constexpr int BMP_HEADER_SIZE  { 40 };
constexpr int BMP_BIT_COUNT_24 { 24 };
constexpr int BMP_BIT_COUNT_32 { 32 };
constexpr int ALIGNMENT = 4; // BMP rows must align to 4-byte boundary

}

bool BMPImage::load(const std::string& filePath)
{
  std::ifstream file(filePath, std::ios::binary);

  if (!file.is_open()) {
    std::cerr << "Failed to open file " << filePath << '\n';
    return false;
  }
  // Step 1: Read BMP headers and validate format
  if (!_readHeaders(file)) {
    std::cerr << "Failed to read headers\n";
    return false;
  }
  // Step 2: Prepare row stride (row length with padding to multiple of 4 bytes)
  m_rowStride = ((m_width * (m_bitCount / 8) + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT;

  // Step 3: Calculate size of the image data
  const int dataSize = m_rowStride * m_height;
  m_data.resize(dataSize);

  // Step 4: Move file pointer to start of pixel data
  file.seekg(m_dataOffset, std::ios::beg);

  // Step 5: Read pixel data
  if (!file.read(reinterpret_cast<char*>(m_data.data()), dataSize)) {
    std::cerr << "Error: Failed to read pixel data\n";
    return false;
  }

  file.close();
  return true;
}


bool BMPImage::_readHeaders(std::ifstream& in)
{
  // Read BMP file header (14 bytes)
  in.read(reinterpret_cast<char*>(&m_fileHeader), sizeof(BMPFileHeader));
  if (m_fileHeader.bfType != BMP_IMAGE_TYPE) {
    std::cerr << "File is not a BMP image\n";
    return false;
  }

  // Read BMP info header (40 bytes)
  in.read(reinterpret_cast<char*>(&m_infoHeader), sizeof(BMPInfoHeader));
  if (m_infoHeader.biSize != BMP_HEADER_SIZE) {
    std::cerr << "Unsupported DIB header size: " << m_infoHeader.biSize << "\n";
    return false;
  }

  // Check supported formats (only 24 or 32 bits per pixel allowed)
  if (m_infoHeader.biBitCount != BMP_BIT_COUNT_24 && m_infoHeader.biBitCount != BMP_BIT_COUNT_32) {
    std::cerr << "Error: Only 24-bit or 32-bit BMPs are supported\n";
    return false;
  }

  // Store basic image metadata
  m_width      = m_infoHeader.biWidth;
  m_height     = std::abs(m_infoHeader.biHeight); // Height can be negative (top-down)
  m_bitCount   = m_infoHeader.biBitCount;
  m_dataOffset = m_fileHeader.bfOffBits;

  return true;
}

void BMPImage::display() const
{
  const bool isBottomUp    = m_infoHeader.biHeight > 0;
  const int  bytesPerPixel = m_bitCount / 8;

  for (int y = 0; y < m_height; ++y) {
    const int rowIndex = isBottomUp ? m_height - 1 - y : y;
    const std::uint8_t* row = m_data.data() + (rowIndex * m_rowStride);
    for (int x = 0; x < m_width; ++x) {
      const std::uint8_t* pixel = row + bytesPerPixel * x;

      const std::uint8_t blue  = pixel[0];
      const std::uint8_t green = pixel[1];
      const std::uint8_t red   = pixel[2];

      // Output ' ' for black, '█' for white
      if (red == 0 && green == 0 && blue == 0) {
        std::cout << " ";
      } else if (red == 255 && green == 255 && blue == 255) {
        std::cout << "█";
      }
    }
    std::cout << '\n';
  }
}

void BMPImage::drawCross()
{
  const RGB color = getColor(RGB::Red);

  _drawLine(Point{0, 0}, Point{m_width - 1, m_height - 1}, color);
  _drawLine(Point{0, m_height - 1}, Point{m_width - 1, 0}, color);
}

void BMPImage::_drawPixel(const Point& p, const RGB& color)
{
  if (!isInside(p)) {
    return ;
  }

  const bool isBottomUp    { m_infoHeader.biHeight > 0 };
  const int  rowIndex      { isBottomUp ? m_height - 1 - p.getY() : p.getY() };
  const int  bytesPerPixel { m_bitCount / 8 };

  std::uint8_t* row   = m_data.data() + (rowIndex * m_rowStride);
  std::uint8_t* pixel = row + bytesPerPixel * p.getX();

  //
  pixel[0] = color.b;
  pixel[1] = color.g;
  pixel[2] = color.r;

  // If 32-bit image: optional alpha/padding (we leave as-is)
}

void BMPImage::_drawLine(const Point& start, const Point& end, const RGB& color)
{
  // Bresenham’s line drawing algorithm
  int x0 = start.getX();
  int y0 = start.getY();
  const int x1 = end.getX();
  const int y1 = end.getY();

  const int dx = std::abs(x1 - x0);
  const int dy = std::abs(y1 - y0);
  const int stepX = (x0 < x1) ? 1 : -1;
  const int stepY = (y0 < y1) ? 1 : -1;

  int err = dx - dy;

  while (true) {
    _drawPixel(Point{x0, y0}, color);

    if (x0 == x1 && y0 == y1)
      break;

    const int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += stepX;
    }

    if (e2 < dx) {
      err += dx;
      y0 += stepY;
    }
  }
}

bool BMPImage::isInside(const Point &p) const noexcept
{
  const int x = p.getX();
  const int y = p.getY();
  return x >= 0 && y >= 0 && x < m_width && y < m_height;
}

bool BMPImage::save(const std::string& filePath) const
{
  std::ofstream out(filePath, std::ios::binary);
  if (!out) {
    std::cerr << "Error: Cannot open file for writing: " << filePath << '\n';
    return false;
  }

  // Write headers
  out.write(reinterpret_cast<const char*>(&m_fileHeader), sizeof(m_fileHeader));
  out.write(reinterpret_cast<const char*>(&m_infoHeader), sizeof(m_infoHeader));

  // Write pixel data
  out.write(reinterpret_cast<const char*>(m_data.data()), m_data.size());

  out.close();
  return true;
}