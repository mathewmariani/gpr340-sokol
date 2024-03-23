// engine
#include "graphics/graphics.h"

// batteries
#include "batteries/colors.h"

#include "greedysearch.h"

bool GreedySearch::Step(World &world)
{
  if (!initialized)
  {
    initialized = true;

    // add to frontier
    auto start = world.GetStart();
    frontier.push_back(*start);
    reached.insert({*start, true});

    return true;
  }

  if (frontier.empty())
  {
    return false;
  }

  /* check for visitable neighbors */
  auto current = frontier.front();
  auto visitables = getVisitables(world, current);

  for (const auto &next : visitables)
  {
    if (!reached.contains(next))
    {
      frontier.push_back(next);
      reached.insert({next, true});
    };
  }

  frontier.erase(frontier.begin());
  // frontier.pop();

  return true;
}

void GreedySearch::Clear(World &world)
{
  initialized = false;
  frontier.clear();
  reached.clear();
  // while (!frontier.empty())
  // {
  //   frontier.pop();
  // }
}

void GreedySearch::Render()
{
  // auto tmp = frontier;
  // while (!tmp.empty())
  // {
  //   auto tile = tmp.front();
  //   engine::graphics::set_color(colors::BlueViolet);
  //   engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_LINE, tile.x * 16, tile.y * 16, 16, 16);
  //   tmp.pop();
  // }

  for (const auto &coord : frontier)
  {
    engine::graphics::set_color(colors::BlueViolet);
    engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_LINE, coord.x * 16, coord.y * 16, 16, 16);
  }
}

std::vector<batteries::grid_location<int>> GreedySearch::getVisitables(World &world, const batteries::grid_location<int> &point)
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

std::vector<batteries::grid_location<int>> GreedySearch::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> neighbors;
  return neighbors;
}