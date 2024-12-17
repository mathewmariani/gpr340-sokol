// engine
#include "graphics/graphics.h"
#include "math/math.h"

#include "world.h"

void World::Resize(int new_width)
{
  width = new_width;
  auto padded_width = width + 1;
  size = padded_width * padded_width;

  maze.resize(padded_width);

  Node *node;
  for (auto j = 0; j < padded_width; ++j)
  {
    for (auto i = 0; i < padded_width; ++i)
    {
      node = &maze.at({i, j});
      node->type = NodeType::Empty;
    }
  }

  // create start
  start = RandomPoint();
  // SetNodeType(start, NodeType::Start);
}

void World::Randomize(float chance)
{
  for (auto y = 0; y < size; ++y)
  {
    for (auto x = 0; x < size; ++x)
    {
      auto rand = engine::math::random(0.0f, 1.0f);
      auto type = (rand < chance) ? NodeType::Empty : NodeType::Wall;
      maze.at({x, y}).type = type;
    }
  }
}

batteries::grid_location<int> World::RandomPoint() const
{
  return {
      engine::math::random(0, width),
      engine::math::random(0, width),
  };
}

Node World::GetNode(const batteries::grid_location<int> &point)
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

static std::unordered_map<NodeType, Colorf> color_map = {
    {NodeType::Empty, LightGray},
    {NodeType::Wall, DarkGray},
    {NodeType::Start, Green},
    {NodeType::Goal, Red},
};

void World::Render()
{
  /* draw background */
  engine::graphics::set_color(color_map[NodeType::Empty]);
  engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, 0, 0, width * 16, width * 16);

  /* draw nodes */
  for (auto j = 0; j < width; ++j)
  {
    for (auto i = 0; i < width; ++i)
    {
      if (GetNodeType({i, j}) == NodeType::Wall)
      {
        engine::graphics::set_color(color_map[NodeType::Wall]);
        engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, i * 16, j * 16, 16, 16);
      }
    }
  }

  /* draw start and goal */
  engine::graphics::set_color(color_map[NodeType::Start]);
  engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, start.x * 16, start.y * 16, 16, 16);
  engine::graphics::set_color(color_map[NodeType::Goal]);
  engine::graphics::rectangle(engine::graphics::DrawMode::DRAW_MODE_FILL, goal.x * 16, goal.y * 16, 16, 16);
}