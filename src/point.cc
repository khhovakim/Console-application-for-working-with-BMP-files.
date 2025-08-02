//
// Created by khovakim on 8/2/25.
//

#include "point.h"

Point &Point::operator+=(const Point &rhs)
{
  m_x += rhs.m_x;
  m_y += rhs.m_y;
  return *this;
}

Point &Point::operator-=(const Point &rhs)
{
  m_x -= rhs.m_x;
  m_y -= rhs.m_y;
  return *this;
}

Point Point::operator+(const Point &rhs) const
{
  Point p = *this;
  p += rhs;
  return p;
}

Point Point::operator-(const Point &rhs) const
{
  Point p = *this;
  p -= rhs;
  return p;
}

bool operator==(const Point& lhs, const Point& rhs)
{
  return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

bool operator!=(const Point& lhs, const Point& rhs)
{
  return !(lhs == rhs);
}
