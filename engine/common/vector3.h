#pragma once

// STL
#include <cmath>
#include <algorithm>

// forward declaration
template <typename T>
class Vector2;
template <typename T>
class Vector4;

template <typename T>
class Vector3
{
  // type definitions
protected:
  using Vector2 = Vector2<T>;
  using Vector4 = Vector4<T>;

  // static variables
public:
  static const Vector3 back;
  static const Vector3 down;
  static const Vector3 forward;
  static const Vector3 left;
  static const Vector3 one;
  static const Vector3 right;
  static const Vector3 up;
  static const Vector3 zero;

  // public variables
public:
  union
  {
    T x;
    T u;
    T r;
  };
  union
  {
    T y;
    T v;
    T g;
  };
  union
  {
    T z;
    T s;
    T b;
  };

  // constructors
public:
  Vector3()
      : x{0}, y{0}, z{0}
  {
  }

  Vector3(T x, T y, T z)
      : x{x}, y{y}, z{z}
  {
  }

  template <class _T>
  Vector3(_T x, _T y, _T z)
      : x{static_cast<T>(x)}, y{static_cast<T>(y)}, z{static_cast<T>(z)}
  {
  }

  template <class _T>
  Vector3(const Vector3<_T> &v)
      : x{static_cast<T>(v.x)}, y{static_cast<T>(v.y)}, z{static_cast<T>(v.z)}
  {
  }

  Vector3(const Vector3 &v)
      : x{v.x}, y{v.y}, z{v.z}
  {
  }

  ~Vector3() = default;

  // operators
public:
  auto operator[](int i) -> T &
  {
    switch (i)
    {
    default:
    case 0:
      return this->x;
    case 1:
      return this->y;
    case 2:
      return this->z;
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
    case 2:
      return this->z;
    }
  }

  auto operator=(const Vector3 &v) -> Vector3 &
  {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return (*this);
  };

  auto operator+(const Vector3 &v) const -> Vector3
  {
    return Vector3{
        this->x + v.x,
        this->y + v.y,
        this->z + v.z};
  }

  auto operator+=(const Vector3 &v) -> Vector3 &
  {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return (*this);
  }

  auto operator-(const Vector3 &v) const -> Vector3
  {
    return Vector3{
        this->x - v.x,
        this->y - v.y,
        this->z - v.z};
  }

  auto operator-=(const Vector3 &v) -> Vector3 &
  {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return (*this);
  }

  auto operator*(const Vector3 &v) const -> Vector3
  {
    return Vector3{
        this->x * v.x,
        this->y * v.y,
        this->z * v.z};
  }

  auto operator*=(const Vector3 &v) -> Vector3 &
  {
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
    return (*this);
  }

  auto operator/(const Vector3 &v) const -> Vector3
  {
    return Vector3{
        this->x / v.x,
        this->y / v.y,
        this->z / v.z};
  }

  auto operator/=(const Vector3 &v) -> Vector3 &
  {
    this->x /= v.x;
    this->y /= v.y;
    this->z /= v.z;
    return (*this);
  }

  auto operator*(const T &s) const -> Vector3
  {
    return Vector3{
        this->x * s,
        this->y * s,
        this->z * s};
  }

  auto operator*=(const T &s) -> Vector3 &
  {
    this->x *= static_cast<T>(s);
    this->y *= static_cast<T>(s);
    this->z *= static_cast<T>(s);
    return (*this);
  }

  auto operator/(const T &s) const -> Vector3
  {
    return Vector3{
        this->x / s,
        this->y / s,
        this->z / s};
  }

  auto operator/=(const T &s) -> Vector3 &
  {
    this->x /= static_cast<T>(s);
    this->y /= static_cast<T>(s);
    this->z /= static_cast<T>(s);
    return (*this);
  }

  auto operator-() const -> Vector3
  {
    return Vector3{
        -this->x,
        -this->y,
        -this->z};
  }

  operator Vector2() const
  {
    return Vector2{
        this->x,
        this->y,
    };
  }

  operator Vector4() const
  {
    return Vector4{
        this->x,
        this->y,
        this->z,
        static_cast<T>(0)};
  }

  // public functions
public:
  /**
   * Returns the length of this vector.
   */
  auto length() const noexcept -> T
  {
    return static_cast<T>(std::sqrt((x * x) + (y * y) + (z * z)));
  }

  /**
   * Returns the magnitude of this vector.
   */
  auto magnitude() const noexcept -> T
  {
    return static_cast<T>(std::sqrt((x * x) + (y * y) + (z * z)));
  }

  /**
   * Makes this vector have a length of 1.
   */
  auto normalize() noexcept -> void
  {
    const auto l = length();
    this->x /= l;
    this->y /= l;
    this->z /= l;
  }

  /**
   * Returns a vector with a length of 1.
   */
  auto normalized() const noexcept -> Vector3
  {
    Vector3 v{*this};
    v.normalize();
    return v;
  }

  /**
   * Returns the squared length of this vector.
   */
  auto sqrLength() const noexcept -> T
  {
    return static_cast<T>((x * x) + (y * y) + (z * z));
  }

  /**
   * Returns the squared length of this vector.
   */
  auto sqrMagnitude() const noexcept -> T
  {
    return static_cast<T>((x * x) + (y * y) + (z * z));
  }

  // static functions
public:
  /**
   * Returns the angle in degrees between a and b.
   * @param  a [description]
   * @param  b [description]
   */
  // static auto angle(const Vector3 &a, const Vector3 &b) -> T {
  // 	return static_cast<T>(std::acos(dot(a, b)));
  // }

  /**
   * Returns the cross product between a and b.
   * @param  a [description]
   * @param  b [description]
   */
  // static auto cross(const Vector3 &a, const Vector3 &b) -> T {
  // 	return static_cast<T>(std::acos(dot(a, b)));
  // }

  /**
   * Returns the distance between a and b.
   * @param  a [description]
   * @param  b [description]
   */
  static auto distance(const Vector3 &a, const Vector3 &b) -> T
  {
    return static_cast<T>(magnitude(b - a));
  }

  /**
   * Returns the dot product of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto dot(const Vector3 &a, const Vector3 &b) -> T
  {
    return static_cast<T>((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
  }

  /**
   * Returns the length of a vector.
   * @param  v [description]
   */
  static auto length(const Vector3 &v) -> T
  {
    return static_cast<T>(std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
  }

  /**
   * Returns the length of a vector.
   * @param  v [description]
   */
  static auto magnitude(const Vector3 &v) -> T
  {
    return static_cast<T>(std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
  }
  /**
   * Returns a vector that is made from the largest components of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto max(const Vector3 &a, const Vector3 &b) -> Vector3
  {
    return Vector3{
        std::max(a.x, b.x),
        std::max(a.y, b.y),
        std::max(a.z, b.z)};
  }

  /**
   * Returns a vector that is made from the smallest components of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto min(const Vector3 &a, const Vector3 &b) -> Vector3
  {
    return Vector3{
        std::min(a.x, b.x),
        std::min(a.y, b.y),
        std::min(a.z, b.z)};
  }

  /**
   * Returns a vector with a length of 1.
   * @param  v [description]
   */
  static auto normalize(const Vector3 &v) -> Vector3
  {
    return Vector3(v) / v.length();
  }

  /**
   * Returns the squared length of a vector.
   * @param  v [description]
   */
  static auto sqrlength(const Vector3 &v) -> T
  {
    return static_cast<T>((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
  }

  /**
   * Returns the squared length of a vector.
   * @param  v [description]
   */
  static auto sqrMagnitude(const Vector3 &v) -> T
  {
    return static_cast<T>((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
  }
}; // vector3

template <typename T>
const Vector3<T> Vector3<T>::back{0, 0, -1};

template <typename T>
const Vector3<T> Vector3<T>::down{0, -1, 0};

template <typename T>
const Vector3<T> Vector3<T>::forward{0, 0, 1};

template <typename T>
const Vector3<T> Vector3<T>::left{-1, 0, 0};

template <typename T>
const Vector3<T> Vector3<T>::one{1, 1, 1};

template <typename T>
const Vector3<T> Vector3<T>::right{1, 0, 0};

template <typename T>
const Vector3<T> Vector3<T>::up{0, 1, 0};

template <typename T>
const Vector3<T> Vector3<T>::zero{0, 0, 0};

typedef Vector3<float> Vector3f;