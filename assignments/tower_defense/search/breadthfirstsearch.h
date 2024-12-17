#pragma once

#include "search.h"

#include <queue>
#include <unordered_map>
#include <vector>

class BreadthFirstSearch : public Search
{
public:
  BreadthFirstSearch() = default;
  std::string GetName() override { return "Breadth First Search"; };

  bool Step(World &world) override;
  void Clear(World &world) override;
  void Render() override;

private:
  std::vector<batteries::grid_location<int>> getVisitables(World &world, const batteries::grid_location<int> &tile);
  std::vector<batteries::grid_location<int>> getVisitedNeighbors(World &world, const batteries::grid_location<int> &tile);

private:
  bool initialized = false;
  std::vector<batteries::grid_location<int>> frontier;
  std::unordered_map<batteries::grid_location<int>, bool> reached;
};