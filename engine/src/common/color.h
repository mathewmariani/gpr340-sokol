#pragma once

template <typename T>
struct ColorT
{
  T r;
  T g;
  T b;
  T a;

  explicit ColorT() : r(0), g(0), b(0), a(1) {}
  explicit ColorT(unsigned int packed)
  {
    a = static_cast<float>((packed >> 24) / 255.0f);
    b = static_cast<float>(((packed << 8) >> 24) / 255.0f);
    g = static_cast<float>(((packed << 16) >> 24) / 255.0f);
    r = static_cast<float>(((packed << 24) >> 24) / 255.0f);
  }

  bool operator==(const ColorT<T> &other) const
  {
    return (r == other.r && g == other.g && b == other.b && a == other.a);
  }
};

typedef ColorT<float> Colorf;