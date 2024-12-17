// engine
#include "common/color.h"
#include "graphics/graphics.h"

#include "breadthfirstsearch.h"

// static std::vector<batteries::grid_location<int>> deltas{
//     batteries::grid_location<int>::up,
//     batteries::grid_location<int>::down,
//     batteries::grid_location<int>::left,
//     batteries::grid_location<int>::right,
// };

bool BreadthFirstSearch::Step(World &world)
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

void BreadthFirstSearch::Clear(World &world)
{
  initialized = false;
  frontier.clear();
  reached.clear();
  // while (!frontier.empty())
  // {
  //   frontier.pop();
  // }
}

void BreadthFirstSearch::Render()
{
  // auto tmp = frontier;
  // while (!tmp.empty())
  // {
  //   auto tile = tmp.front();
  //   engine::graphics::set_color(BlueViolet);
  //   engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_LINE, tile.x * 16, tile.y * 16, 16, 16);
  //   tmp.pop();
  // }

  for (const auto &coord : frontier)
  {
    engine::graphics::set_color(BlueViolet);
    engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_LINE, coord.x * 16, coord.y * 16, 16, 16);
  }
}

std::vector<batteries::grid_location<int>> BreadthFirstSearch::getVisitables(World &world, const batteries::grid_location<int> &point)
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

std::vector<batteries::grid_location<int>> BreadthFirstSearch::getVisitedNeighbors(World &world, const batteries::grid_location<int> &point)
{
  std::vector<batteries::grid_location<int>> neighbors;
  return neighbors;
}