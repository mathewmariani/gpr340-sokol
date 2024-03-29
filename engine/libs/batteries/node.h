#pragma once

#include <cstdint>

struct Node
{
public:
  Node() = default;
  Node(bool north, bool east, bool south, bool west)
  {
    data = ((uint8_t)north) | ((uint8_t)east << 1U) | ((uint8_t)south << 2U) | ((uint8_t)west << 3U);
  }

private:
  uint8_t data;

public:
  bool inline GetNorth() const { return data & 1U; };
  bool inline GetEast() const { return data >> 1U & 1U; };
  bool inline GetSouth() const { return data >> 2U & 1U; };
  bool inline GetWest() const { return data >> 3U & 1U; };

  void inline SetNorth(bool x) { data = (data & ~(1 << 0)) | x << 0; };
  void inline SetEast(bool x) { data = (data & ~(1 << 1)) | x << 1; };
  void inline SetSouth(bool x) { data = (data & ~(1 << 2)) | x << 2; };
  void inline SetWest(bool x) { data = (data & ~(1 << 3)) | x << 3; };
};