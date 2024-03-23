#pragma once

#include "mazegenerator.h"

#include <queue>

class HuntAndKill : public MazeGenerator
{
public:
  HuntAndKill() = default;
  std::string GetName() override { return "Hunt and Kill"; };

  bool Step(World &world) override;
  void Clear(World &world) override;

private:
  std::vector<batteries::grid_location<int>> getVisitables(World &world, const batteries::grid_location<int> &point);
  std::vector<batteries::grid_location<int>> getVisitedNeighbors(World &world, const batteries::grid_location<int> &point);

private:
  bool initialized = false;
  std::queue<batteries::grid_location<int>> frontier;
};