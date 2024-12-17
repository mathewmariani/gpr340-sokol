#pragma once

#include "mazegenerator.h"

#include <vector>

class RandomWalk : public MazeGenerator
{
public:
  RandomWalk() = default;
  std::string GetName() override { return "Random Walk"; };

  bool Step(World &world) override;
  void Clear(World &world) override;

private:
  std::vector<batteries::grid_location<int>> getVisitables(World &world, const batteries::grid_location<int> &point);
  std::vector<batteries::grid_location<int>> getVisitedNeighbors(World &world, const batteries::grid_location<int> &point);

private:
  bool initialized = false;
  std::vector<batteries::grid_location<int>> frontier;
};