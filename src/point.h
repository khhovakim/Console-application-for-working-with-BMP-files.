//
// Created by khovakim on 8/2/25.
//

#ifndef   POINT_H
# define  POINT_H


class Point {
public:
  explicit Point(const int x = 0, const int y = 0)
    : m_x{x}, m_y{y} {}
  ~Point() = default;

public:
  [[nodiscard]] int getX() const noexcept { return m_x; }
  [[nodiscard]] int getY() const noexcept { return m_y; }

  void setX(const int x) { m_x = x; }
  void setY(const int y) { m_y = y; }

  void makeAbsoluteX();
  void makeAbsoluteY();

  void makeNegativeX();
  void makeNegativeY();
public:
  Point& operator+=(const Point& rhs);
  Point& operator-=(const Point& rhs);

  Point operator+(const Point& rhs) const;
  Point operator-(const Point& rhs) const;

public:
  explicit operator int() const noexcept { return m_x + m_y; }
private:
  int m_x;
  int m_y;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
#endif // POINT_H
