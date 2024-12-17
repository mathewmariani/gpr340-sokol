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
private:
  struct GridNode
  {
    int cost;
    batteries::grid_location<int> location;

    bool operator<(const GridNode &other) const
    {
      return cost < other.cost;
    }
  };

public:
  AStarSearch() = default;
  std::string GetName() override { return "A* Search"; };

  std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> Find(World &world, const batteries::grid_location<int> &start) override;

private:
  std::vector<batteries::grid_location<int>> getVisitables(World &world, const batteries::grid_location<int> &tile);
  std::vector<batteries::grid_location<int>> getVisitedNeighbors(World &world, const batteries::grid_location<int> &tile);
};