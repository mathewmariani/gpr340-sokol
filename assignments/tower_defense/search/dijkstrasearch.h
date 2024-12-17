#pragma once

#include "search.h"

#include <queue>
#include <unordered_map>
#include <vector>

class DijkstraSearch : public Search
{
public:
  DijkstraSearch() = default;
  std::string GetName() override { return "Dijkstra's Algorithm"; };

  std::unordered_map<batteries::grid_location<int>, batteries::grid_location<int>> Find(World &world, const batteries::grid_location<int> &start) override;

private:
  std::vector<batteries::grid_location<int>> getVisitables(World &world, const batteries::grid_location<int> &tile);
  std::vector<batteries::grid_location<int>> getVisitedNeighbors(World &world, const batteries::grid_location<int> &tile);
};