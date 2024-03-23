#pragma once

#include <unordered_map>
#include <vector>

enum class GridNeighborhood
{
  MooresNeighborhood,
  VonNewmanNeighborhood,
};

template <typename T>
struct Cell
{
  T x, y;
  Cell(T x_, T y_) : x(x_), y(y_) {}
  Cell<T> operator+(const Cell<T> &rhs) const
  {
    return {x + rhs.x, y + rhs.y};
  }
  Cell<T> operator-(const Cell<T> &rhs) const
  {
    return {x - rhs.x, y - rhs.y};
  }
  Cell<T> &operator=(const Cell<T> &rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return (*this);
  };
  bool operator==(const Cell &other) const
  {
    return (x == other.x && y == other.y);
  }
};

template class Cell<int>;

struct HashCell
{
  std::size_t operator()(const Cell<int> &c) const noexcept
  {
    auto hq = std::hash<int>{}(c.x);
    auto hr = std::hash<int>{}(c.y);
    return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
  }
};

template <class T>
class Cellgrid
{
public:
  Cellgrid() : width(0) {}
  Cellgrid(int width_) : width(width_)
  {
    resize(width);
  }

  /* container */
public:
  auto begin() const { return map.begin(); }
  auto end() const { return map.end(); }
  const auto cbegin() const { return map.begin(); }
  const auto cend() const { return map.end(); }

  auto contains(const Cell<int> &cell) const { return map.contains(cell); }

  auto &at(const Cell<int> &cell) { return map.at(cell); }
  const auto &at(const Cell<int> &cell) const { return map.at(cell); }

  const auto size() const { return map.size(); }
  const auto side_length() const { return width; }

  void clear()
  {
    map.clear();
  }
  void resize(int new_width)
  {
    width = new_width;

    map.reserve(new_width);
//    map.clear();
    for (auto y = 0; y <= new_width; ++y)
    {
      for (auto x = 0; x <= new_width; ++x)
      {
        map[{x, y}] = T();
      }
    }
  }

  /* cellgrid */
public:
  // NOTE: use GridNeighborhood.
  auto neighbors(const Cell<int> &cell) const
  {
    /* FIXME: can this be `constexpr` */
    static std::vector<Cell<int>> deltas{
        Cell(-1, -1),
        Cell(+0, -1),
        Cell(+1, -1),
        Cell(-1, +0),
        Cell(+1, +0),
        Cell(-1, +1),
        Cell(+0, +1),
        Cell(+1, +1),
    };
    std::vector<Cell<int>> ret;
    for (const auto &dt : deltas)
    {
      auto n = cell + dt;
    }
    return ret;
  }

public:
  // static void cell_to_pixel(const CellOrientation &M, const Cell<int> &cell, float width, float *x, float *y);
  // static Cell<float> pixel_to_cell(const CellOrientation &M, float width, int x, int y);
  // static Cell<int> cell_round(Cell<float> h);

private:
  std::size_t width;
  std::unordered_map<Cell<int>, T, HashCell> map;
};

// template <class T>
// void Cellgrid<T>::cell_to_pixel(const CellOrientation &M, const Cell<int> &cell, float size, float *x, float *y)
// {
//   *x = (M.f0 * cell.q_ + M.f1 * cell.r_) * size;
//   *y = (M.f2 * cell.q_ + M.f3 * cell.r_) * size;
// }

// template <class T>
// Cell<float> Cellgrid<T>::pixel_to_cell(const CellOrientation &M, float size, int x, int y)
// {
//   auto px = (x / size);
//   auto py = (y / size);
//   auto q = M.b0 * px + M.b1 * py;
//   auto r = M.b2 * px + M.b3 * py;
//   return {q, r, -q - r};
// }

// template <class T>
// Cell<int> Cellgrid<T>::cell_round(Cell<float> h)
// {
//   auto q = (int)std::round(h.q());
//   auto r = (int)std::round(h.r());
//   auto s = (int)std::round(h.s());
//   auto q_diff = std::abs(q - h.q());
//   auto r_diff = std::abs(r - h.r());
//   auto s_diff = std::abs(s - h.s());
//   if (q_diff > r_diff && q_diff > s_diff)
//   {
//     q = -r - s;
//   }
//   else if (r_diff > s_diff)
//   {
//     r = -q - s;
//   }
//   else
//   {
//     s = -q - r;
//   }
//   return {q, r, s};
// }
