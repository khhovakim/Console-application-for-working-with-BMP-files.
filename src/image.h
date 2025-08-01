//
// Created by khovakim on 7/31/25.
//

#ifndef   IMAGE_H
# define  IMAGE_H

# include <string> // For std::string

class Image
{
public:
  virtual ~Image() = default;

public:
  virtual bool load(const std::string& filePath) = 0;
  [[nodiscard]] virtual bool save(const std::string& filepath) const = 0;

  virtual void display() const = 0;

  [[nodiscard]] virtual int getWidth()  const noexcept = 0;
  [[nodiscard]] virtual int getHeight() const noexcept = 0;
};

#endif // IMAGE_H
