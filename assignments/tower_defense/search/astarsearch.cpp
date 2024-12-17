// engine
#include "graphics/graphics.h"

#include "astarsearch.h"
#include "../heuristic/heuristic.h"

bool AStarSearch::Step(World &world)
{
  if (!initialized)
  {
    initialized = true;

    // add to frontier
    auto start = world.GetStart();
    frontier.push((GridNode){.cost = 0, .location = *start});
    reached.insert({*start, true});

    return true;
  }

  if (frontier.empty())
  {
    return false;
  }

  /* check for visitable neighbors */
  auto current = frontier.top().location;
  auto visitables = getVisitables(world, current);

  int priority = 0;
  for (const auto &next : visitables)
  {
    if (!reached.contains(next))
    {
      // priority = ManhattanDistance(goal, next)
      frontier.push((GridNode){.cost = priority, .location = next});
      reached.insert({next, true});
    };
  }

  frontier.pop();

  return true;
}

void AStarSearch::Clear(World &world)
{
  initialized = false;
  while (!frontier.empty())
  {
    frontier.pop();
  }
  reached.clear();
}

void AStarSearch::Render()
{
  auto tmp = frontier;
  while (!tmp.empty())
  {
    auto tile = tmp.top().location;
    engine::graphics::set_color(BlueViolet);
    engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_LINE, tile.x * 16, tile.y * 16, 16, 16);
    tmp.pop();
  }
}

std::vector<batteries::grid_location<int>> AStarSearch::getVisitables(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> visitables;
  batteries::grid_location<int> next{0, 0};

  for (const auto &delta : batteries::grid_location<int>::VonNewmanNeighborhood)
  {
    next = point + delta;
    if (IsPositionInBounds(world, next) && (world.GetNodeType(next) != NodeType::Wall))
    {
      visitables.emplace_back(next);
    }
  }

  return visitables;
}

std::vector<batteries::grid_location<int>> AStarSearch::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> neighbors;
  return neighbors;
}