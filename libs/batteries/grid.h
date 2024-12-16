#pragma once

#include <vector>

template <class T>
class Grid
{
public:
  Grid() = default;
  Grid(int width, int height) : width(width), height(height) { data.reserve(width * height); }
  Grid(Grid<T> &grid) { data = grid.data; }
  ~Grid() { data.clear(); }

  T &operator()(int x, int y) { return data[x + y * width]; }
  const T &operator()(int x, int y) const { return data[x + y * width]; }

  T Get(int x, int y) const { return data[x + y * width]; }
  void Set(int x, int y, T value) { data[x + y * width] = value; }

  void Clear()
  {
    data.clear();
  }

  void Resize(int width, int height)
  {
    this->width = width;
    this->height = height;
    data.resize(width * height);
  }

private:
  int width = 0;
  int height = 0;

  std::vector<T> data;
};