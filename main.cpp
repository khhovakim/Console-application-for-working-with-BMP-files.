//
// Created by khovakim on 7/31/25.
//
#include <iostream>
#include <string>

#include "BMPImage.h"

int main() {
  BMPImage image;

  std::string inputFile;
  std::cout << ">> Enter input BMP file name: ";
  std::getline(std::cin, inputFile);

  if (!image.load(inputFile)) {
    std::cerr << "Failed to load BMP file.\n";
    return 1;
  }

  std::cout << "Original image:\n";
  image.display();

  image.drawLine(0, 0, 10000, 10000); // will be clipped
  image.drawLine(0, image.getHeight() - 1, image.getWidth() - 1, 0); // draw cross

  std::cout << "Image with cross:\n";
  image.display();

  std::string outputFile;
  std::cout << ">> Enter output BMP file name: ";
  std::getline(std::cin, outputFile);

  if (!image.save(outputFile)) {
    std::cerr << "Failed to save BMP file.\n";
    return 1;
  }

  return 0;
}