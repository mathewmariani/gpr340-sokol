#pragma once

#include <vector>

template <class T>
class Graph
{
public:
  Graph() = default;
  Graph(int width, int height) : width(width), height(height) { data.reserve(width * height); }
  Graph(Graph<T> &grid) { data = grid.data; }
  ~Graph() { data.clear(); }

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
  std::vector<Node> edges;
};