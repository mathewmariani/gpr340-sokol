#pragma once

// batteries
#include "batteries/finite_grid.h"
#include "batteries/grid_location.h"

enum class NodeType
{
  Unvisited,
  Frontier,
  Visited,
};

struct MazeNode
{
  bool north_edge;
  bool west_edge;
  NodeType type;
};

// FIXME: rename this to something more desciptive
class World
{
public:
  void Resize(int size);

  MazeNode GetNode(const batteries::grid_location<int> &point);

  const NodeType GetNodeType(const batteries::grid_location<int> &point) const;
  void SetNodeType(const batteries::grid_location<int> &point, NodeType type);

  bool GetNorth(const batteries::grid_location<int> &point);
  bool GetEast(const batteries::grid_location<int> &point);
  bool GetSouth(const batteries::grid_location<int> &point);
  bool GetWest(const batteries::grid_location<int> &point);

  void SetNorth(const batteries::grid_location<int> &point, const bool &state);
  void SetEast(const batteries::grid_location<int> &point, const bool &state);
  void SetSouth(const batteries::grid_location<int> &point, const bool &state);
  void SetWest(const batteries::grid_location<int> &point, const bool &state);

  const int Size() const { return size; }
  const int Width() const { return width; }

  void Render();

private:
  int size;
  int width;
  batteries::finite_grid<MazeNode> maze;
};