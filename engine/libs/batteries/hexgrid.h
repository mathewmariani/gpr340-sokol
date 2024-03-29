#pragma once

#include <unordered_map>
#include <vector>

namespace
{
  struct HexOrientation
  {
    float f0;
    float f1;
    float f2;
    float f3;
    float b0;
    float b1;
    float b2;
    float b3;
    float start_angle;
    HexOrientation(float f0_, float f1_, float f2_, float f3_, float b0_, float b1_, float b2_, float b3_, float start_angle_) : f0(f0_), f1(f1_), f2(f2_), f3(f3_), b0(b0_), b1(b1_), b2(b2_), b3(b3_), start_angle(start_angle_) {}
  };

  static HexOrientation layout_pointy{
      1.73205080757f, 1.73205080757f / 2.0f, 0.0f, 3.0f / 2.0f,
      1.73205080757f / 3.0f, -1.0f / 3.0f, 0.0f, 2.0f / 3.0f,
      0.5f};
  static HexOrientation layout_flat{
      3.0f / 2.0f, 0.0f, 1.73205080757f / 2.0f, 1.73205080757f,
      2.0f / 3.0f, 0.0f, -1.0f / 3.0f, 1.73205080757f / 3.0f,
      0.0f};
}

template <typename T>
struct Hex
{
  T q_, r_;
  Hex(T q, T r, T s) : q_(q), r_(r)
  {
    // assert(q + r + s == 0);
  }

  Hex<T> operator+(const Hex<T> &rhs) const
  {
    return {q() + rhs.q(), r() + rhs.r(), s() + rhs.s()};
  }

  Hex<T> operator-(const Hex<T> &rhs) const
  {
    return {q() - rhs.q(), r() - rhs.r(), s() - rhs.s()};
  }

  Hex<T> &operator=(const Hex<T> &rhs)
  {
    q_ = rhs.q();
    r_ = rhs.r();
    return (*this);
  };

  bool operator==(const Hex &other) const
  {
    return (q_ == other.q_ && r_ == other.r_);
  }

  inline T q() const { return q_; }
  inline T r() const { return r_; }
  inline T s() const { return -q_ - r_; }
};

template class Hex<int>;
template class Hex<float>;

struct HashHex
{
  std::size_t operator()(const Hex<int> &h) const noexcept
  {
    auto hq = std::hash<int>{}(h.q_);
    auto hr = std::hash<int>{}(h.r_);
    return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
  }
};

template <class T>
class Hexgrid
{
public:
  Hexgrid() : width(0) {}
  Hexgrid(int width_) : width(width_)
  {
    resize(width);
  }

  /* container */
public:
  auto begin() const { return map.begin(); }
  auto end() const { return map.end(); }
  const auto cbegin() const { return map.begin(); }
  const auto cend() const { return map.end(); }

  auto contains(const Hex<int> &hex) const { return map.contains(hex); }

  auto &at(const Hex<int> &hex) { return map.at(hex); }
  const auto &at(const Hex<int> &hex) const { return map.at(hex); }

  const auto size() const { map.size(); }
  void clear()
  {
    map.clear();
  }
  void resize(int new_width)
  {
    width = new_width;
    map.clear();
    for (auto q = -new_width; q <= new_width; q++)
    {
      auto r1 = std::max(-new_width, -q - new_width);
      auto r2 = std::min(new_width, -q + new_width);
      for (auto r = r1; r <= r2; r++)
      {
        map.insert({{q, r, -q - r}, false});
      }
    }
  }

  /* hexgrid */
public:
  void set_hex_size(void);
  void set_radius(void);

  auto get_radius(void) const { return width; }

  auto neighbors(const Hex<int> &hex)
  {
    /* FIXME: can this be `constexpr` */
    std::vector<Hex<int>> deltas{
        Hex(+1, 0, -1),
        Hex(+1, -1, 0),
        Hex(0, -1, +1),
        Hex(-1, 0, +1),
        Hex(-1, +1, 0),
        Hex(0, +1, -1),
    };

    std::vector<Hex<int>> ret;
    for (const auto &n : deltas)
    {
      ret.emplace_back(hex + n);
    }
    return ret;
  }

public:
  static void hex_to_pixel(const HexOrientation &M, const Hex<int> &hex, float width, float *x, float *y);
  static Hex<float> pixel_to_hex(const HexOrientation &M, float width, int x, int y);
  static Hex<int> hex_round(Hex<float> h);

private:
  std::size_t width;
  std::unordered_map<Hex<int>, T, HashHex> map;
};

template <class T>
void Hexgrid<T>::hex_to_pixel(const HexOrientation &M, const Hex<int> &hex, float size, float *x, float *y)
{
  *x = (M.f0 * hex.q_ + M.f1 * hex.r_) * size;
  *y = (M.f2 * hex.q_ + M.f3 * hex.r_) * size;
}

template <class T>
Hex<float> Hexgrid<T>::pixel_to_hex(const HexOrientation &M, float size, int x, int y)
{
  auto px = (x / size);
  auto py = (y / size);
  auto q = M.b0 * px + M.b1 * py;
  auto r = M.b2 * px + M.b3 * py;
  return {q, r, -q - r};
}

template <class T>
Hex<int> Hexgrid<T>::hex_round(Hex<float> h)
{
  auto q = (int)std::round(h.q());
  auto r = (int)std::round(h.r());
  auto s = (int)std::round(h.s());
  auto q_diff = std::abs(q - h.q());
  auto r_diff = std::abs(r - h.r());
  auto s_diff = std::abs(s - h.s());
  if (q_diff > r_diff && q_diff > s_diff)
  {
    q = -r - s;
  }
  else if (r_diff > s_diff)
  {
    r = -q - s;
  }
  else
  {
    s = -q - r;
  }
  return {q, r, s};
}