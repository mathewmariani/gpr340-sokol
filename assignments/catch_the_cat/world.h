#pragma once

/* batteries */
#include "batteries/hexgrid.h"

class Catcher;
class Cat;

class World
{
public:
  void Resize(int size);

  const int Size() const { return size; }

  void Render();

private:
  // Catcher catcher;
  // Cat cat;

private:
  int size;
  Hexgrid<bool> grid;
};