#pragma once

// batteries
#include "batteries/finite_grid.h"
#include "batteries/grid_location.h"

enum class NodeType
{
  Empty,
  Wall,
  Start,
  Goal,
};

// FIXME: rename this to something more desciptive
class World
{
public:
  void Resize(int size);
  void Randomize(float chance);
  batteries::grid_location<int> RandomPoint() const;

  NodeType GetNode(const batteries::grid_location<int> &point);

  const NodeType GetNodeType(const batteries::grid_location<int> &point) const;
  void SetNodeType(const batteries::grid_location<int> &point, NodeType type);

  const int Size() const { return size; }
  const int Width() const { return width; }

  void Render();

private:
  int size;
  int width;
  batteries::finite_grid<NodeType> grid;
};