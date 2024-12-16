#pragma once

// batteries
#include "batteries/grid_location.h"

#include "search.h"

#include <queue>
#include <unordered_map>
#include <vector>
#include <tuple>

class AStarSearch : public Search
{
public:
  AStarSearch() = default;
  std::string GetName() override { return "A* Search"; };

  bool Step(World &world) override;
  void Clear(World &world) override;
  void Render() override;

private:
  std::vector<batteries::grid_location<int>> getVisitables(World &world, const batteries::grid_location<int> &tile);
  std::vector<batteries::grid_location<int>> getVisitedNeighbors(World &world, const batteries::grid_location<int> &tile);

private:
  bool initialized = false;
  std::priority_queue<std::tuple<batteries::grid_location<int>, int>> frontier;
  // std::vector<batteries::grid_location<int>> frontier;
  std::unordered_map<batteries::grid_location<int>, bool> reached;
};