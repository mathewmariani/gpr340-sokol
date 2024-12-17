#pragma once

// STL
#include <cmath>

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEG2RAD(x) ((x * M_PI) / 180.0)

// forward declaration
template <typename T>
class Matrix4;
template <typename T>
class Vector3;

template <typename T>
class Quaternion
{
  // type definitions
protected:
  using Matrix4 = Matrix4<T>;
  // using Vector3 = Vector3<T>;

  // public variables
public:
  T w, x, y, z;

  // static variables
public:
  static const Quaternion identity;

  // constructors
public:
  Quaternion()
      : w{0}, x{0}, y{0}, z{0}
  {
  }

  Quaternion(T w, T x, T y, T z)
      : w{w}, x{x}, y{y}, z{z}
  {
  }

  template <class _T>
  Quaternion(_T w, _T x, _T y, _T z)
      : w{static_cast<T>(w)}, x{static_cast<T>(x)}, y{static_cast<T>(y)}, z{static_cast<T>(z)}
  {
  }

  Quaternion(T w, const Vector3<T> &v)
      : w{w}, x{v.x}, y{v.y}, z{v.z}
  {
  }

  template <class _T>
  Quaternion(_T w, const Vector3<_T> &v)
      : x{static_cast<T>(v.x)}, y{static_cast<T>(v.y)}, z{static_cast<T>(v.z)}, w{static_cast<T>(w)}
  {
  }

  Quaternion(const Quaternion &q)
      : w{q.w}, x{q.x}, y{q.y}, z{q.z}
  {
  }

  ~Quaternion() = default;

  // operators
public:
  auto operator[](int i) -> T &
  {
    switch (i)
    {
    default:
    case 0:
      return this->w;
    case 1:
      return this->x;
    case 2:
      return this->y;
    case 3:
      return this->z;
    }
  }

  auto operator[](int i) const -> const T &
  {
    switch (i)
    {
    default:
    case 0:
      return this->w;
    case 1:
      return this->x;
    case 2:
      return this->y;
    case 3:
      return this->z;
    }
  }

  auto operator=(const Quaternion &q) -> Quaternion &
  {
    this->w = q.w;
    this->x = q.x;
    this->y = q.y;
    this->z = q.z;
    return (*this);
  }

  auto operator~() const -> Quaternion
  {
    return Quaternion{
        this->w,
        -this->x,
        -this->y,
        -this->z};
  }

  auto operator-() const -> Quaternion
  {
    return Quaternion{
        -this->w,
        -this->x,
        -this->y,
        -this->z};
  }

  auto operator+(const Quaternion &q) const -> Quaternion
  {
    return Quaternion{
        this->w + q.w,
        this->x + q.x,
        this->y + q.y,
        this->z + q.z};
  }

  auto operator+=(const Quaternion &q) -> Quaternion &
  {
    this->w += q.w;
    this->x += q.x;
    this->y += q.y;
    this->z += q.z;
    return (*this);
  }

  auto operator-(const Quaternion &q) const -> Quaternion
  {
    return Quaternion{
        this->w - q.w,
        this->x - q.x,
        this->y - q.y,
        this->z - q.z};
  }

  auto operator-=(const Quaternion &q) -> Quaternion &
  {
    this->w -= q.w;
    this->x -= q.x;
    this->y -= q.y;
    this->z -= q.z;
    return (*this);
  }

  auto operator*(const Quaternion &q) const -> Quaternion
  {
    const auto &lhs = *this;
    const auto &rhs = q;

    const auto w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
    const auto x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
    const auto y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
    const auto z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;

    return Quaternion{w, x, y, z};
  }

  auto operator*=(const Quaternion &q) -> Quaternion &
  {
    this->w *= q.w;
    this->x *= q.x;
    this->y *= q.y;
    this->z *= q.z;
    return (*this);
  }

  auto operator*(const T s) const -> Quaternion
  {
    return Quaternion{
        this->w * s,
        this->x * s,
        this->y * s,
        this->z * s};
  }

  auto operator*=(const T s) -> Quaternion &
  {
    this->w *= s;
    this->x *= s;
    this->y *= s;
    this->z *= s;
    return (*this);
  }

  auto operator/(const T s) const -> Quaternion
  {
    return Quaternion{
        this->w / s,
        this->x / s,
        this->y / s,
        this->z / s};
  }

  auto operator/=(const T s) -> Quaternion &
  {
    this->w /= s;
    this->x /= s;
    this->y /= s;
    this->z /= s;
    return (*this);
  }

  // public functions
public:
  /**
   * Returns the inverse of this rotation.
   * @param  q [description]
   */
  auto inverse() noexcept -> Quaternion
  {
    normalize();
    return -(*this);
  }

  /**
   * Returns the inverse of this rotation.
   * @param  q [description]
   */
  auto inverted() const noexcept -> Quaternion
  {
    Quaternion q{*this};
    q.inverse();
    return q;
  }

  /**
   * Returns the length of this Quaternion.
   */
  auto length() const noexcept -> T
  {
    return static_cast<T>(std::sqrt((x * x) + (y * y) + (z * z) + (w * w)));
  }

  /**
   * Returns the magnitude of this Quaternion.
   */
  auto magnitude() const noexcept -> T
  {
    return static_cast<T>(std::sqrt((x * x) + (y * y) + (z * z) + (w * w)));
  }

  /**
   * Makes this Quaternion have a length of 1.
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
   * Returns a Quaternion with a length of 1.
   */
  auto normalized() const noexcept -> Quaternion
  {
    Quaternion q{*this};
    q.normalize();
    return q;
  }

  auto rotatePoint(const Quaternion &q) const -> Vector3<T>
  {
    auto &rotation = *this;
    auto result = rotation * q * ~rotation;
    return Vector3<T>{result.x, result.y, result.z};
  }

  auto rotatePoint(const Vector3<T> &p) const -> Vector3<T>
  {
    return rotatePoint(Quaternion{0, p});
  }

  auto rotatePoint(const T x, const T y, const T z) const -> Vector3<T>
  {
    return rotatePoint(Quaternion{0, x, y, z});
  }

  /**
   * Returns the square length of this Quaternion.
   */
  auto sqrLength() const noexcept -> T
  {
    return static_cast<T>((x * x) + (y * y) + (z * z) + (w * w));
  }

  /**
   * Returns the square magnitude of this Quaternion.
   */
  auto sqrMagnitude() const noexcept -> T
  {
    return static_cast<T>((x * x) + (y * y) + (z * z) + (w * w));
  }

  auto transform() const -> Matrix4
  {
    Matrix4 ret;

    const auto xx = x * x;
    const auto xy = x * y;
    const auto xz = x * z;
    const auto xw = x * w;

    const auto yy = y * y;
    const auto yz = y * z;
    const auto yw = y * w;

    const auto zz = z * z;
    const auto zw = z * w;

    ret[0] = 1 - 2 * (yy + zz);
    ret[4] = 2 * (xy - zw);
    ret[8] = 2 * (xz + yw);
    ret[12] = 0;

    ret[1] = 2 * (xy + zw);
    ret[5] = 1 - 2 * (xx + zz);
    ret[9] = 2 * (yz - xw);
    ret[13] = 0;

    ret[2] = 2 * (xz - yw);
    ret[6] = 2 * (yz + xw);
    ret[10] = 1 - 2 * (xx + yy);
    ret[14] = 0;

    ret[3] = 0;
    ret[7] = 0;
    ret[11] = 0;
    ret[15] = 1;

    return ret;
  }

  // static functions
public:
  /**
   * Returns Quaternion as rotation around axis (angles in degrees).
   * @param  deg [description]
   * @param  axis [description]
   */
  static auto angleAxis(float deg, Vector3<T> axis) -> Quaternion
  {
    axis.normalize();
    const auto rads = float(deg) * 0.0174532925f;
    const auto c = std::cosf(rads / 2.0f);
    const auto s = std::sinf(rads / 2.0f);
    return Quaternion{c, axis * s};
  }

  /**
   * Returns Quaternion as rotation around axis (angles in degrees).
   * @param  deg [description]
   * @param  x [description]
   * @param  y [description]
   * @param  z [description]
   */
  static auto angleAxis(float deg, T x, T y, T z) -> Quaternion
  {
    auto v = Vector3<T>{x, y, z};
    return Quaternion::angleAxis(deg, v);
  }

  /**
   * Returns the dot product between two rotations.
   * @param  a [description]
   * @param  b [description]
   */
  static auto dot(const Quaternion &a, const Quaternion &b) -> T
  {
    return static_cast<T>(std::sqrt((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w)));
  }

  /**
   * Returns a rotation from eulers angles.
   * @param  x Rotation around x axis (in degrees).
   * @param  y Rotation around y axis (in degrees).
   * @param  z Rotation around z axis (in degrees).
   */
  static auto euler(T x, T y, T z) -> Quaternion
  {
    return Quaternion{
        angleAxis(x, Vector3<T>(1, 0, 0)) *
        angleAxis(y, Vector3<T>(0, 1, 0)) *
        angleAxis(z, Vector3<T>(0, 0, 1))};
  }

  /**
   * Returns the inverse of a rotation.
   * @param  q [description]
   */
  static auto inverse(Quaternion &q) -> Quaternion
  {
    q.normalize();
    return -q;
  }

  /**
   * Returns the length of a Quaternion.
   * @param  q [description]
   */
  static auto length(const Quaternion &q) -> T
  {
    return static_cast<T>(std::sqrt((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w)));
  }

  /**
   * Returns the magnitude of a Quaternion.
   * @param  q [description]
   */
  static auto magnitude(const Quaternion &q) -> T
  {
    return static_cast<T>(std::sqrt((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w)));
  }

  /**
   * Returns a vector with a length of 1.
   * @param  q [description]
   */
  static auto normalize(const Quaternion &q) -> Quaternion
  {
    return Quaternion(q) / q.length();
  }

  /**
   * Returns the square length of a Quaternion.
   * @param  q [description]
   */
  static auto sqrLength(const Quaternion &q) -> T
  {
    return static_cast<T>((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w));
  }

  /**
   * Returns the square magnitude of a Quaternion.
   * @param  q [description]
   */
  static auto sqrMagnitude(const Quaternion &q) -> T
  {
    return static_cast<T>((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w));
  }
}; // quaternion

template <typename T>
const Quaternion<T> Quaternion<T>::identity{1, 0, 0, 0};
