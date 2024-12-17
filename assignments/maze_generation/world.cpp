// graphics
#include "graphics/graphics.h"

#include "world.h"

void World::Resize(int new_width)
{
  width = new_width;
  auto padded_width = width + 1;
  size = padded_width * padded_width;

  maze.resize(padded_width);

  MazeNode *node;
  for (auto j = 0; j < padded_width; ++j)
  {
    for (auto i = 0; i < padded_width; ++i)
    {
      node = &maze.at({i, j});
      node->north_edge = (i < width) ? true : false;
      node->west_edge = (j < width) ? true : false;
      node->type = NodeType::Unvisited;
    }
  }
}

MazeNode World::GetNode(const batteries::grid_location<int> &point)
{
  return maze.at(point);
}

const NodeType World::GetNodeType(const batteries::grid_location<int> &point) const
{
  return maze.at(point).type;
}

void World::SetNodeType(const batteries::grid_location<int> &point, NodeType type)
{
  maze.at(point).type = type;
}

#define NORTH_OF(point) maze.at(point).north_edge
#define EAST_OF(point) maze.at(point + batteries::grid_location<int>::East).west_edge
#define SOUTH_OF(point) maze.at(point + batteries::grid_location<int>::North).north_edge
#define WEST_OF(point) maze.at(point).west_edge

bool World::GetNorth(const batteries::grid_location<int> &point)
{
  return NORTH_OF(point);
}

bool World::GetEast(const batteries::grid_location<int> &point)
{
  return EAST_OF(point);
}

bool World::GetSouth(const batteries::grid_location<int> &point)
{
  return SOUTH_OF(point);
}

bool World::GetWest(const batteries::grid_location<int> &point)
{
  return WEST_OF(point);
}

void World::SetNorth(const batteries::grid_location<int> &point, const bool &state)
{
  NORTH_OF(point) = state;
}

void World::SetEast(const batteries::grid_location<int> &point, const bool &state)
{
  EAST_OF(point) = state;
}

void World::SetSouth(const batteries::grid_location<int> &point, const bool &state)
{
  SOUTH_OF(point) = state;
}

void World::SetWest(const batteries::grid_location<int> &point, const bool &state)
{
  WEST_OF(point) = state;
}

static std::unordered_map<NodeType, Colorf> color_map = {
    {NodeType::Unvisited, LightGray},
    {NodeType::Frontier, Salmon},
    {NodeType::Visited, Black},
};

void World::Render()
{
  batteries::grid_location<int> point{0, 0};

  int x0, y0;
  int x1, y1;
  int x2, y2;

  /* draw nodes */
  for (auto j = 0; j < width; ++j)
  {
    for (auto i = 0; i < width; ++i)
    {
      point = {i, j};
      engine::graphics::set_color(color_map[GetNodeType(point)]);
      engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, i * 16, j * 16, 16, 16);
    }
  }

  /* draw edges */
  engine::graphics::set_color(1.0f, 1.0f, 1.0f, 1.0f);
  for (auto j = 0; j < width + 1; ++j)
  {
    for (auto i = 0; i < width + 1; ++i)
    {
      point = {i, j};
      x0 = i * 16, y0 = j * 16;
      x1 = x0 + 16, y1 = y0;
      x2 = x0, y2 = y0 + 16;
      if (GetNorth(point))
      {
        engine::graphics::line(x0, y0, x1, y1);
      }
      if (GetWest(point))
      {
        engine::graphics::line(x0, y0, x2, y2);
      }
    }
  }
}
