#include "math.h"
#include "common/math.h"

namespace
{
  static struct
  {
    std::random_device random_device;
  } state;
}

namespace engine
{
  namespace math
  {
    void setup(void)
    {
    }

    void cleanup(void)
    {
    }

    int random(int min, int max)
    {
      if (min == max)
      {
        return min;
      }
      std::mt19937 rng(state.random_device());
      std::uniform_int_distribution<int> dist(min, max);
      return dist(rng);
    }

    float random(float min, float max)
    {
      if (min == max)
      {
        return min;
      }
      std::mt19937 rng(state.random_device());
      std::uniform_real_distribution<float> dist(min, max);
      return dist(rng);
    }
  }
}