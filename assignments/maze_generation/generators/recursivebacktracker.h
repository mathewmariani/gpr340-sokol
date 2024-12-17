#pragma once

#include "mazegenerator.h"

#include <stack>

class RecursiveBacktracker : public MazeGenerator
{
public:
  RecursiveBacktracker() = default;
  std::string GetName() override { return "Recursive Backtracker"; };

  bool Step(World &world) override;
  void Clear(World &world) override;

private:
  std::vector<batteries::grid_location<int>> getVisitables(World &world, const batteries::grid_location<int> &point);
  std::vector<batteries::grid_location<int>> getVisitedNeighbors(World &world, const batteries::grid_location<int> &point);

private:
  bool initialized = false;
  std::stack<batteries::grid_location<int>> frontier;
};