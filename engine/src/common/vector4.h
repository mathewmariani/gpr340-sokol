#pragma once

// STL
#include <cmath>

// forward declaration
template <typename T>
class Vector2;
template <typename T>
class Vector3;

template <typename T>
class Vector4
{
  // type definitions
protected:
  using Vector2 = Vector2<T>;
  using Vector3 = Vector3<T>;

  // static variables
public:
  static const Vector4 one;
  static const Vector4 zero;

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
  union
  {
    T w;
    T t;
    T a;
  };

  // constructors
public:
  Vector4()
      : x{0}, y{0}, z{0}, w{0}
  {
  }

  Vector4(T x, T y, T z, T w)
      : x{x}, y{y}, z{z}, w{w}
  {
  }

  template <class _T>
  Vector4(_T x, _T y, _T z, _T w)
      : x{static_cast<T>(x)}, y{static_cast<T>(y)}, z{static_cast<T>(z)}, w{static_cast<T>(w)}
  {
  }

  Vector4(const Vector4 &v)
      : x{v.x}, y{v.y}, z{v.z}, w{v.w}
  {
  }

  template <class _T>
  Vector4(const Vector4<_T> &v)
      : x{static_cast<T>(v.x)}, y{static_cast<T>(v.y)}, z{static_cast<T>(v.z)}, w{static_cast<T>(v.w)}
  {
  }

  ~Vector4() = default;

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
    case 3:
      return this->w;
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
    case 3:
      return this->w;
    }
  }

  auto operator=(const Vector4 &v) -> Vector4 &
  {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
    return (*this);
  };

  auto operator+(const Vector4 &v) const -> Vector4
  {
    return Vector4{
        this->x + v.x,
        this->y + v.y,
        this->z + v.z,
        this->w + v.w};
  }

  auto operator+=(const Vector4 &v) -> Vector4 &
  {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    this->w += v.w;
    return (*this);
  }

  auto operator-(const Vector4 &v) const -> Vector4
  {
    return Vector4{
        this->x - v.x,
        this->y - v.y,
        this->z - v.z,
        this->w - v.w};
  }

  auto operator-=(const Vector4 &v) -> Vector4 &
  {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    this->w -= v.w;
    return (*this);
  }

  auto operator*(const Vector4 &v) const -> Vector4
  {
    return Vector4{
        this->x * v.x,
        this->y * v.y,
        this->z * v.z,
        this->w * v.w};
  }

  auto operator*=(const Vector4 &v) -> Vector4 &
  {
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
    this->w *= v.w;
    return (*this);
  }

  auto operator/(const Vector4 &v) const -> Vector4
  {
    return Vector4{
        this->x / v.x,
        this->y / v.y,
        this->z / v.z,
        this->w / v.w};
  }

  auto operator/=(const Vector4 &v) -> Vector4 &
  {
    this->x /= v.x;
    this->y /= v.y;
    this->z /= v.z;
    this->w /= v.w;
    return (*this);
  }

  auto operator*(const T &s) const -> Vector4
  {
    return Vector4{
        this->x * s,
        this->y * s,
        this->z * s,
        this->w * s};
  }

  auto operator*=(const T &s) -> Vector4 &
  {
    this->x *= static_cast<T>(s);
    this->y *= static_cast<T>(s);
    this->z *= static_cast<T>(s);
    this->w *= static_cast<T>(s);
    return (*this);
  }

  auto operator/(const T &s) const -> Vector4
  {
    return Vector4{
        this->x / s,
        this->y / s,
        this->z / s,
        this->w / s};
  }

  auto operator/=(const T &s) -> Vector4 &
  {
    this->x /= static_cast<T>(s);
    this->y /= static_cast<T>(s);
    this->z /= static_cast<T>(s);
    this->w /= static_cast<T>(s);
    return (*this);
  }

  auto operator-() const -> Vector4
  {
    return Vector4{
        -this->x,
        -this->y,
        -this->z,
        -this->w};
  }

  operator Vector2() const
  {
    return Vector2{
        this->x,
        this->y,
    };
  }

  operator Vector3() const
  {
    return Vector3{
        this->x,
        this->y,
        this->z,
    };
  }

  // public functions
public:
  /**
   * Returns the length of this vector.
   */
  auto length() const noexcept -> T
  {
    return static_cast<T>(std::sqrt((x * x) + (y * y) + (z * z) + (w * w)));
  }

  /**
   * Returns the magnitude of this vector.
   */
  auto magnitude() const noexcept -> T
  {
    return static_cast<T>(std::sqrt((x * x) + (y * y) + (z * z) + (w * w)));
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
    this->w /= l;
  }

  /**
   * Returns a vector with a length of 1.
   */
  auto normalized() const noexcept -> Vector4
  {
    Vector4 v{*this};
    v.normalize();
    return v;
  }

  /**
   * Returns the squared length of this vector.
   */
  auto sqrLength() const noexcept -> T
  {
    return static_cast<T>((x * x) + (y * y) + (z * z) + (w * w));
  }

  /**
   * Returns the squared length of this vector.
   */
  auto sqrMagnitude() const noexcept -> T
  {
    return static_cast<T>((x * x) + (y * y) + (z * z) + (w * w));
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
  static auto distance(const Vector4 &a, const Vector4 &b) -> T
  {
    return static_cast<T>(magnitude(b - a));
  }

  /**
   * Returns the dot product of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto dot(const Vector4 &a, const Vector4 &b) -> T
  {
    return static_cast<T>((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
  }

  /**
   * Returns the length of a vector.
   * @param  v [description]
   */
  static auto length(const Vector4 &v) -> T
  {
    return static_cast<T>(std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)));
  }

  /**
   * Returns the length of a vector.
   * @param  v [description]
   */
  static auto magnitude(const Vector4 &v) -> T
  {
    return static_cast<T>(std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)));
  }

  /**
   * Returns a vector that is made from the largest components of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto max(const Vector4 &a, const Vector4 &b) -> Vector4
  {
    return Vector4{
        std::max(a.x, b.x),
        std::max(a.y, b.y),
        std::max(a.z, b.z),
        std::max(a.w, b.w)};
  }

  /**
   * Returns a vector that is made from the smallest components of two vectors.
   * @param  a [description]
   * @param  b [description]
   */
  static auto min(const Vector4 &a, const Vector4 &b) -> Vector4
  {
    return Vector4{
        std::min(a.x, b.x),
        std::min(a.y, b.y),
        std::min(a.z, b.z),
        std::min(a.w, b.w)};
  }

  /**
   * Returns a vector with a length of 1.
   * @param  v [description]
   */
  static auto normalize(const Vector4 &v) -> Vector4
  {
    return Vector4(v) / v.length();
  }

  /**
   * Returns the squared length of a vector.
   * @param  v [description]
   */
  static auto sqrLength(const Vector4 &v) -> T
  {
    return static_cast<T>((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
  }

  /**
   * Returns the squared length of a vector.
   * @param  v [description]
   */
  static auto sqrMagnitude(const Vector4 &v) -> T
  {
    return static_cast<T>((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
  }
}; // vector4

template <typename T>
const Vector4<T> Vector4<T>::one{1, 1, 1, 1};

template <typename T>
const Vector4<T> Vector4<T>::zero{0, 0, 0, 0};
