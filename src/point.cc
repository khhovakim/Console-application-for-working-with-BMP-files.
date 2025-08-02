//
// Created by khovakim on 8/2/25.
//

#include "point.h"

#include <cmath>  // For std::abs

void Point::makeAbsoluteX()
{
  m_x = std::abs(m_x);
}

void Point::makeAbsoluteY()
{
  m_y = std::abs(m_x);
}

void Point::makeNegativeX()
{
  if (m_x > 0) {
    m_x = -m_x;
  }
}

void Point::makeNegativeY()
{
  if (m_y > 0) {
    m_y = -m_y;
  }
}
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
