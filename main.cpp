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

  image.drawCross(); // draw cross

  std::string outputFile;
  std::cout << ">> Enter output BMP file name: ";
  std::getline(std::cin, outputFile);

  if (!image.save(outputFile)) {
    std::cerr << "Failed to save BMP file.\n";
    return 1;
  }

  std::cout << "Image saved successfully!\n";
  return 0;
}