#pragma once

#include "object.h"

class Goal : public Object
{
public:
  Goal() = default;
  virtual ~Goal() = default;

  std::string GetName() override { return "Goal Object"; };
};