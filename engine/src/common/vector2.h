#pragma once

// STL
#include "common/math.h"
#include <cmath>
#include <algorithm>

// forward declaration
template <typename T>
class Vector3;
template <typename T>
class Vector4;

template <typename T>
class Vector2
{
  // type definitions
protected:
  using Vector3 = Vector3<T>;
  using Vector4 = Vector4<T>;

  // static variables
public:
  static Vector2 down;
  static Vector2 left;
  static Vector2 one;
  static Vector2 right;
  static Vector2 up;
  static Vector2 zero;

  // public variables
public:
  union
  {
    T x;
    T u;
  };
  union
  {
    T y;
    T v;
  };

  // constructors
public:
  Vector2()
      : x{0}, y{0}
  {
  }

  Vector2(T x, T y)
      : x{x}, y{y}
  {
  }

  template <class _T>
  Vector2(_T x, _T y)
      : x{static_cast<T>(x)}, y{static_cast<T>(y)}
  {
  }

  template <class _T>
  Vector2(const Vector2<_T> &v)
      : x{static_cast<T>(v.x)}, y{static_cast<T>(v.y)}
  {
  }

  Vector2(const Vector2 &v)
      : x{v.x}, y{v.y}
  {
  }

  ~Vector2() = default;

  // operators
public:
  auto operator==(const Vector2 &rhs) const -> bool
  {
    return (x == rhs.x && y == rhs.y);
  }

  auto operator[](int i) -> T &
  {
    switch (i)
    {
    default:
    case 0:
      return this->x;
    case 1:
      return this->y;
    }
  }

  auto operator[](int i) const -> const T &
  {
    switch (i)
    {
    default:
    case 0:
      return this->x;
    case 1:
      return this->y;
    }
  }

  auto operator=(const Vector2 &v) -> Vector2 &
  {
    this->x = v.x;
    this->y = v.y;
    return (*this);
  };

  auto operator+(const Vector2 &v) const -> Vector2
  {
    return Vector2{
        this->x + v.x,
        this->y + v.y};
  }

  auto operator+=(const Vector2 &v) -> Vector2 &
  {
    this->x += v.x;
    this->y += v.y;
    return (*this);
  }

  auto operator-(const Vector2 &v) const -> Vector2
  {
    return Vector2{
        this->x - v.x,
        this->y - v.y};
  }

  auto operator-=(const Vector2 &v) -> Vector2 &
  {
    this->x -= v.x;
    this->y -= v.y;
    return (*this);
  }

  auto operator*(const Vector2 &v) const -> Vector2
  {
    return Vector2{
        this->x * v.x,
        this->y * v.y};
  }

  auto operator*=(const Vector2 &v) -> Vector2 &
  {
    this->x *= v.x;
    this->y *= v.y;
    return (*this);
  }

  auto operator/(const Vector2 &v) const -> Vector2
  {
    return Vector2{
        this->x / v.x,
        this->y / v.y};
  }

  auto operator/=(const Vector2 &v) -> Vector2 &
  {
    this->x /= v.x;
    this->y /= v.y;
    return (*this);
  }

  auto operator*(const T &s) const -> Vector2
  {
    return Vector2{
        this->x * s,
        this->y * s};
  }

  auto operator*=(const T &s) -> Vector2 &
  {
    this->x *= static_cast<T>(s);
    this->y *= static_cast<T>(s);
    return (*this);
  }

  auto operator/(const T &s) const -> Vector2
  {
    return Vector2{
        this->x / s,
        this->y / s};
  }

  auto operator/=(const T &s) -> Vector2 &
  {
    this->x /= static_cast<T>(s);
    this->y /= static_cast<T>(s);
    return (*this);
  }

  auto operator-() const -> Vector2
  {
    return Vector2{
        -this->x,
        -this->y};
  }

  operator Vector3() const
  {
    return Vector3{
        this->x,
        this->y,
        static_cast<T>(0)};
  }

  operator Vector4() const
  {
    return Vector4{
        this->x,
        this->y,
        static_cast<T>(0),
        static_cast<T>(0)};
  }

  // public functions
public:
  /**
   * Returns the length of this vector.
   */
  auto length() const noexcept -> T
  {
    return static_cast<T>(std::sqrt((x * x) + (y * y)));
  }

  /**
   * Returns the magnitude of this vector.
   */
  auto magnitude() const noexcept -> T
  {
    return static_cast<T>(std::sqrt((x * x) + (y * y)));
  }

  /**
   * Makes this vector have a length of 1.
   */
  auto normalize() noexcept -> void
  {
    const auto l = length();
    if (l == 0)
    {
      return;
    }
    this->x /= l;
    this->y /= l;
  }

  /**
   * Returns a vector with a length of 1.
   */
  auto normalized() const noexcept -> Vector2
  {
    Vector2 v{*this};
    v.normalize();
    return v;
  }

  auto rotate(T degrees) const noexcept -> Vector2
  {
    const auto sin = std::sin(ENGINE_RAD(degrees));
    const auto cos = std::cos(ENGINE_RAD(degrees));
    return {(cos * x) - (sin * y), (sin * x) + (cos * y)};
  };

  static auto sqrDistance(const Vector2 &a, const Vector2 &b) -> T
  {
    return static_cast<T>(sqrMagnitude(b - a));
  }

  /**
   * Returns the squared length of this vector.
   */
  auto sqrLength() const noexcept -> T
  {
    return static_cast<T>((x * x) + (y * y));
  }

  /**
   * Returns the squared length of this vector.
   */
  auto sqrMagnitude() const noexcept -> T
  {
    return static_cast<T>((x * x) + (y * y));
  }

  // static functions
public:
  /**
   * Returns the angle in degrees between a and b.
   * @param  a [description]
   * @param  b [description]
   */
  // static auto angle(const Vector2 &a, const Vector2 &b) -> T {
  // 	return static_cast<T>(std::acos(dot(a, b)));
  // }

  /**
   * Returns the cross product between a and b.
   * @param  a [description]
   * @param  b [description]
   */
  // static auto cross(const Vector2 &a, const Vector2 &b) -> T {
  // 	return static_cast<T>(std::acos(dot(a, b)));
  // }

  /**
   * Returns the distance between a and b.
   * @param  a [description]
   * @param  b [description]
   */
  static auto distance(const Vector2 &a, const Vector2 &b) -> T
  {
    return static_cast<T>(magnitude(b - a));
  }

  /**
   * Returns the dot product of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto dot(const Vector2 &a, const Vector2 &b) -> T
  {
    return static_cast<T>((a.x * b.x) + (a.y * b.y));
  }

  /**
   * Returns the length of a vector.
   * @param  v [description]
   */
  static auto length(const Vector2 &v) -> T
  {
    return static_cast<T>(std::sqrt((v.x * v.x) + (v.y * v.y)));
  }

  /**
   * Returns the length of a vector.
   * @param  v [description]
   */
  static auto magnitude(const Vector2 &v) -> T
  {
    return static_cast<T>(std::sqrt((v.x * v.x) + (v.y * v.y)));
  }

  /**
   * Returns a vector that is made from the largest components of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto max(const Vector2 &a, const Vector2 &b) -> Vector2
  {
    return Vector2{
        std::max(a.x, b.x),
        std::max(a.y, b.y)};
  }

  /**
   * Returns a vector that is made from the smallest components of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto min(const Vector2 &a, const Vector2 &b) -> Vector2
  {
    return Vector2{
        std::min(a.x, b.x),
        std::min(a.y, b.y)};
  }

  /**
   * Returns a vector with a length of 1.
   * @param  v [description]
   */
  static auto normalize(const Vector2 &v) -> Vector2
  {
    return Vector2(v) / v.length();
  }

  /**
   * Returns the squared length of a vector.
   * @param  v [description]
   */
  static auto sqrlength(const Vector2 &v) -> T
  {
    return static_cast<T>((v.x * v.x) + (v.y * v.y));
  }

  /**
   * Returns the squared length of a vector.
   * @param  v [description]
   */
  static auto sqrMagnitude(const Vector2 &v) -> T
  {
    return static_cast<T>((v.x * v.x) + (v.y * v.y));
  }
}; // vector2

template <typename T>
Vector2<T> Vector2<T>::down{0, -1};

template <typename T>
Vector2<T> Vector2<T>::left{-1, 0};

template <typename T>
Vector2<T> Vector2<T>::one{1, 1};

template <typename T>
Vector2<T> Vector2<T>::right{1, 0};

template <typename T>
Vector2<T> Vector2<T>::up{0, 1};

template <typename T>
Vector2<T> Vector2<T>::zero{0, 0};

typedef Vector2<float> Vector2f;