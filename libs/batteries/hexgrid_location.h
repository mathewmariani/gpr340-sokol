#pragma once

#include <array>
#include <vector>

namespace batteries
{
  template <typename T>
  struct hexgrid_location
  {
    static std::array<hexgrid_location<T>, 6> Neighborhood;
    static std::array<hexgrid_location<T>, 6> Diagonals;

    T q_, r_;
    hexgrid_location(T q, T r, T s) : q_(q), r_(r) {}

    hexgrid_location<T> operator+(const hexgrid_location<T> &rhs) const
    {
      return {q() + rhs.q(), r() + rhs.r(), s() + rhs.s()};
    }

    hexgrid_location<T> operator-(const hexgrid_location<T> &rhs) const
    {
      return {q() - rhs.q(), r() - rhs.r(), s() - rhs.s()};
    }

    hexgrid_location<T> &operator=(const hexgrid_location<T> &rhs)
    {
      q_ = rhs.q();
      r_ = rhs.r();
      return (*this);
    };

    bool operator==(const hexgrid_location &other) const
    {
      return (q_ == other.q_ && r_ == other.r_);
    }

    inline T q() const { return q_; }
    inline T r() const { return r_; }
    inline T s() const { return -q_ - r_; }
  };

  template <typename T>
  std::array<hexgrid_location<T>, 6> hexgrid_location<T>::Neighborhood{
      hexgrid_location<T>{+1, 0, -1},
      hexgrid_location<T>{+1, -1, 0},
      hexgrid_location<T>{0, -1, +1},
      hexgrid_location<T>{-1, 0, +1},
      hexgrid_location<T>{-1, +1, 0},
      hexgrid_location<T>{0, +1, -1},
  };

  template <typename T>
  std::array<hexgrid_location<T>, 6> hexgrid_location<T>::Diagonals{
      hexgrid_location<T>{+2, -1, -1},
      hexgrid_location<T>{+1, -2, +1},
      hexgrid_location<T>{-1, -1, +2},
      hexgrid_location<T>{-2, +1, +1},
      hexgrid_location<T>{-1, +2, -1},
      hexgrid_location<T>{+1, +1, -2},
  };

  template class hexgrid_location<int>;
  template class hexgrid_location<float>;
}

template <>
struct std::hash<batteries::hexgrid_location<int>>
{
  std::size_t operator()(const batteries::hexgrid_location<int> &h) const noexcept
  {
    auto hq = std::hash<int>{}(h.q_);
    auto hr = std::hash<int>{}(h.r_);
    return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
  }
};