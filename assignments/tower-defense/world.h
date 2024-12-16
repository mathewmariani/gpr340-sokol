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

enum class PathfindingType
{
  Unvisited,
  Frontier,
  Visited,
};

struct Node
{
  NodeType type;
  PathfindingType pathfinding;
};

// FIXME: rename this to something more desciptive
class World
{
public:
  void Resize(int size);
  void Randomize(float chance);
  batteries::grid_location<int> RandomPoint() const;

  Node GetNode(const batteries::grid_location<int> &point);

  const NodeType GetNodeType(const batteries::grid_location<int> &point) const;
  void SetNodeType(const batteries::grid_location<int> &point, NodeType type);

  const int Size() const { return size; }
  const int Width() const { return width; }

  void Render();

  inline batteries::grid_location<int> *GetStart() { return &start; }
  inline batteries::grid_location<int> *GetGoal() { return &goal; }

private:
  batteries::grid_location<int> start{0, 0};
  batteries::grid_location<int> goal{0, 0};

  int size;
  int width;
  batteries::finite_grid<Node> maze;
};