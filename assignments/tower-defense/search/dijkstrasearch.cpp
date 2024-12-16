// engine
#include "graphics/graphics.h"

// batteries
#include "batteries/colors.h"

#include "dijkstrasearch.h"

bool DijkstraSearch::Step(World &world)
{
  if (!initialized)
  {
    initialized = true;

    // add to frontier
    auto start = world.GetStart();
    frontier.push_back(*start);
    distance.insert({*start, 0});

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
    if (!distance.contains(next))
    {
      frontier.push_back(next);
      distance.insert({next, 1 + distance[current]});
    };
  }

  frontier.erase(frontier.begin());
  // frontier.pop();

  return true;
}

void DijkstraSearch::Clear(World &world)
{
  initialized = false;
  frontier.clear();
  distance.clear();
  // while (!frontier.empty())
  // {
  //   frontier.pop();
  // }
}

void DijkstraSearch::Render()
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

std::vector<batteries::grid_location<int>> DijkstraSearch::getVisitables(World &world, const batteries::grid_location<int> &point)
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

std::vector<batteries::grid_location<int>> DijkstraSearch::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> neighbors;
  return neighbors;
}