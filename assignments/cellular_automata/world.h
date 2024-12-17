#pragma once

#include "batteries/finite_grid.h"

struct Cell
{
  uint8_t value;
  Cell() : value(0x00) {}
  Cell(uint8_t value_) : value(value_) {}
};

class World
{
public:
  void Resize(int size);
  void SwapBuffers();
  void Randomize(float chance);

  int GetNeighbourhood(int x, int y) const;

  Cell Get(int x, int y) const;
  void Set(int x, int y, const Cell &value);

  void SetNext(int x, int y, const Cell &value);

  const int Size() const { return size; }

  void Render();

private:
  int size;
  int buffer_index;
  batteries::finite_grid<Cell> buffer[2];
};