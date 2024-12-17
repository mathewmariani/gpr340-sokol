#pragma once

#include <vector>

namespace batteries
{
  template <typename T>
  struct hexgrid_location
  {
    static hexgrid_location<T> NorthWest;
    static hexgrid_location<T> North;
    static hexgrid_location<T> NorthEast;
    static hexgrid_location<T> East;
    static hexgrid_location<T> SouthEast;
    static hexgrid_location<T> South;

    static std::vector<hexgrid_location<T>> Neighborhood;

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
  hexgrid_location<T> hexgrid_location<T>::NorthWest{+1, 0, -1};
  template <typename T>
  hexgrid_location<T> hexgrid_location<T>::North{+1, -1, 0};
  template <typename T>
  hexgrid_location<T> hexgrid_location<T>::NorthEast{0, -1, +1};
  template <typename T>
  hexgrid_location<T> hexgrid_location<T>::East{-1, 0, +1};
  template <typename T>
  hexgrid_location<T> hexgrid_location<T>::SouthEast{-1, +1, 0};
  template <typename T>
  hexgrid_location<T> hexgrid_location<T>::South{0, +1, -1};

  template <typename T>
  std::vector<hexgrid_location<T>> hexgrid_location<T>::Neighborhood{
      hexgrid_location<T>::NorthWest,
      hexgrid_location<T>::North,
      hexgrid_location<T>::NorthEast,
      hexgrid_location<T>::East,
      hexgrid_location<T>::SouthEast,
      hexgrid_location<T>::South,
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