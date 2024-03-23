#pragma once

// STL
#include <cmath>
#include <algorithm>

// forward declaration
template <typename T>
class Quaternion;
template <typename T>
class Vector2;
template <typename T>
class Vector3;
template <typename T>
class Vector4;

template <typename T>
class Matrix4
{
  // type definitions
protected:
  using Quaternion = Quaternion<T>;
  using Vector2 = Vector2<T>;
  using Vector3 = Vector3<T>;
  using Vector4 = Vector4<T>;

  // static variables
public:
  // static const Matrix4 identity;
  // static const Matrix4 zero;

  // constructors
public:
  Matrix4()
  {
    memset(e, 0, sizeof(T) * 16);
  }

  Matrix4(const T elements[16])
  {
    memcpy(e, elements, sizeof(T) * 16);
  }

  Matrix4(const Matrix4 &m)
  {
    memcpy(e, m.e, sizeof(T) * 16);
  }

  ~Matrix4() = default;

  // operators
public:
  auto operator=(const Matrix4 &m) -> Matrix4 &
  {
    std::memcpy(e, m.e, sizeof(T) * 16);
    return (*this);
  }

  auto operator[](int i) -> T &
  {
    return e[i];
  }

  auto operator[](int i) const -> const T &
  {
    return e[i];
  }

  auto operator*() -> T *
  {
    return &e[0];
  }

  auto operator*() const -> const T *
  {
    return &e[0];
  }

  auto operator*(const Matrix4 &m) const -> Matrix4
  {
    Matrix4<T> t;
    t.e[0] = (e[0] * m.e[0]) + (e[4] * m.e[1]) + (e[8] * m.e[2]) + (e[12] * m.e[3]);
    t.e[4] = (e[0] * m.e[4]) + (e[4] * m.e[5]) + (e[8] * m.e[6]) + (e[12] * m.e[7]);
    t.e[8] = (e[0] * m.e[8]) + (e[4] * m.e[9]) + (e[8] * m.e[10]) + (e[12] * m.e[11]);
    t.e[12] = (e[0] * m.e[12]) + (e[4] * m.e[13]) + (e[8] * m.e[14]) + (e[12] * m.e[15]);

    t.e[1] = (e[1] * m.e[0]) + (e[5] * m.e[1]) + (e[9] * m.e[2]) + (e[13] * m.e[3]);
    t.e[5] = (e[1] * m.e[4]) + (e[5] * m.e[5]) + (e[9] * m.e[6]) + (e[13] * m.e[7]);
    t.e[9] = (e[1] * m.e[8]) + (e[5] * m.e[9]) + (e[9] * m.e[10]) + (e[13] * m.e[11]);
    t.e[13] = (e[1] * m.e[12]) + (e[5] * m.e[13]) + (e[9] * m.e[14]) + (e[13] * m.e[15]);

    t.e[2] = (e[2] * m.e[0]) + (e[6] * m.e[1]) + (e[10] * m.e[2]) + (e[14] * m.e[3]);
    t.e[6] = (e[2] * m.e[4]) + (e[6] * m.e[5]) + (e[10] * m.e[6]) + (e[14] * m.e[7]);
    t.e[10] = (e[2] * m.e[8]) + (e[6] * m.e[9]) + (e[10] * m.e[10]) + (e[14] * m.e[11]);
    t.e[14] = (e[2] * m.e[12]) + (e[6] * m.e[13]) + (e[10] * m.e[14]) + (e[14] * m.e[15]);

    t.e[3] = (e[3] * m.e[0]) + (e[7] * m.e[1]) + (e[11] * m.e[2]) + (e[15] * m.e[3]);
    t.e[7] = (e[3] * m.e[4]) + (e[7] * m.e[5]) + (e[11] * m.e[6]) + (e[15] * m.e[7]);
    t.e[11] = (e[3] * m.e[8]) + (e[7] * m.e[9]) + (e[11] * m.e[10]) + (e[15] * m.e[11]);
    t.e[15] = (e[3] * m.e[12]) + (e[7] * m.e[13]) + (e[11] * m.e[14]) + (e[15] * m.e[15]);
    return t;
  }

  auto operator*=(const Matrix4 &m) -> Matrix4 &
  {
    return (*this = *this * m);
  }

  auto operator*(const T s) const -> Matrix4
  {
    Matrix4<T> ret;
    for (auto i = 0; i < 16; ++i)
    {
      ret.e[i] = e[i] * s;
    }
    return ret;
  }

  auto operator*=(const T s) -> Matrix4 &
  {
    for (auto i = 0; i < 16; ++i)
    {
      e[i] *= s;
    }
    return (*this);
  }

  auto operator/(const T s) const -> Matrix4
  {
    Matrix4<T> ret;
    for (auto i = 0; i < 16; ++i)
    {
      ret.e[i] = e[i] / s;
    }
    return ret;
  }

  auto operator/=(const T s) -> Matrix4 &
  {
    for (auto i = 0; i < 16; ++i)
    {
      e[i] /= s;
    }
    return (*this);
  }

  auto operator*(const Vector3 &v) const -> Vector3
  {
    const auto &rhs = v;
    return Vector3{
        e[0] * rhs.x + e[4] * rhs.y + e[8] * rhs.z,
        e[1] * rhs.x + e[5] * rhs.y + e[9] * rhs.z,
        e[2] * rhs.x + e[6] * rhs.y + e[10] * rhs.z};
  }

  auto operator*(const Vector4 &v) const -> Vector4
  {
    const auto &rhs = v;
    return Vector4{
        e[0] * rhs.x + e[4] * rhs.y + e[8] * rhs.z + e[12] * rhs.w,
        e[1] * rhs.x + e[5] * rhs.y + e[9] * rhs.z + e[13] * rhs.w,
        e[2] * rhs.x + e[6] * rhs.y + e[10] * rhs.z + e[14] * rhs.w,
        e[3] * rhs.x + e[7] * rhs.y + e[11] * rhs.z + e[15] * rhs.w};
  }

  // public functions
public:
  /**
   * Sets this matrix to the identity matrix.
   */
  auto setIdentity() noexcept -> void
  {
    memset(e, 0, sizeof(T) * 16);
    e[0] = 1.0f;
    e[5] = 1.0f;
    e[10] = 1.0f;
    e[15] = 1.0f;
  }

  /**
   * Sets this matrix to a translation matrix.
   */
  auto setTranslation(const Vector3 &v) noexcept -> void
  {
    /**
     * Matrix4 Translation
     * | 1       |
     * |   1     |
     * |     1   |
     * | x y z w |
     */
    setIdentity();
    e[12] = v.x;
    e[13] = v.y;
    e[14] = v.z;
  }

  /**
   * Sets this matrix to a scale matrix.
   */
  auto setScale(const Vector3 &v) noexcept -> void
  {
    /**
     * Matrix4 Scale
     * | sx      |
     * |   sy    |
     * |     sz  |
     * |       1 |
     */
    setIdentity();
    e[0] = v.x;
    e[5] = v.y;
    e[10] = v.z;
  }

  /**
   * Sets this matrix to a rotation matrix.
   */
  auto setRotation(const Quaternion &q) noexcept -> void
  {
    setIdentity();
  }

  /**
   * Sets this matrix to a transformation matrix.
   */
  auto setTransformation(const Vector3 &position, const Quaternion &q, const Vector3 &scale) noexcept -> void
  {
    setIdentity();
  }

  auto transformXY(Vector2 *coords, int size) const -> void
  {
    for (int i = 0; i < size; i++)
    {
      auto x = (e[0] * coords[i].x) + (e[4] * coords[i].y) + (0) + (e[12]);
      auto y = (e[1] * coords[i].x) + (e[5] * coords[i].y) + (0) + (e[13]);
      coords[i].x = x;
      coords[i].y = y;
    }
  }

  // static functions
public:
  /**
   * Returns an indentity matrix.
   */
  static auto identity() -> Matrix4
  {
    /**
     * Matrix4 Identity
     * | 1       |
     * |   1     |
     * |     1   |
     * |       1 |
     */
    Matrix4<T> m;
    m[0] = 1.0f;
    m[5] = 1.0f;
    m[10] = 1.0f;
    m[15] = 1.0f;
    return m;
  }

  /**
   * Returns a translation matrix.
   * @param  x [description]
   * @param  y [description]
   * @param  z [description]
   * @param  w [description]
   */
  auto translate(T x, T y, T z, T w = 1) -> void
  {
    /**
     * Matrix4 Translation
     * | 1       |
     * |   1     |
     * |     1   |
     * | x y z w |
     */
    Matrix4 t;
    t.setTranslation({x, y, z});
    (*this) = (*this) * t;
  }

  /**
   * Returns a scaling matrix.
   * @param  s [description]
   */
  auto scale(T s) -> void
  {
    /**
     * Matrix4 Scale
     * | sx      |
     * |   sy    |
     * |     sz  |
     * |       1 |
     */
    e[0] = s;
    e[5] = s;
    e[10] = s;
  }

  /**
   * Returns a rotation matrix.
   * @param  a [description]
   * @param  x [description]
   * @param  y [description]
   * @param  z [description]
   */
  auto rotate(T d, Vector3 a) -> void
  {
    // const auto rads = float(d) * 0.0174532925f;
    const auto c = std::cosf(d);
    const auto s = std::sinf(d);
    const auto ux = (a.x * a.x);
    const auto uy = (a.y * a.y);
    const auto uz = (a.z * a.z);

    e[0] = (c + ux * (1 - c));
    e[1] = ((a.y * a.x) * (1 - c) + a.z * s);
    e[2] = ((a.z * a.x) * (1 - c) - a.y * s);
    e[4] = ((a.x * a.y) * (1 - c) - a.z * s);
    e[5] = (c + uy * (1 - c));
    e[6] = ((a.z * a.y) * (1 - c) + a.x * s);
    e[8] = ((a.x * a.z) * (1 - c) + a.y * s);
    e[9] = ((a.y * a.z) * (1 - c) - a.x * s);
    e[10] = (c + uz * (1 - c));
  }

  static auto rotate(Quaternion q) -> void
  {
    // TODO: ...
  }

  /**
   * Returns a rotation matrix about the x-axis.
   * @param  a [description]
   */
  auto rotateX(T a) -> void
  {
    /**
     * Matrix4 Rotation X
     * | 1       |
     * |   c s   |
     * |  -s c   |
     * |       1 |
     */
    // const auto rads = float(a) * 0.0174532925f;
    const auto c = std::cosf(a);
    const auto s = std::sinf(a);

    auto t = Matrix4::identity();
    t[5] = (c);
    t[6] = (s);
    t[9] = (-s);
    t[10] = (c);

    (*this) = (*this) * t;
  }

  /**
   * Returns a rotation matrix about the y-axis.
   * @param  a [description]
   */
  static auto rotateY(T a) -> Matrix4
  {
    /**
     * Matrix4 Rotation Y
     * | c  -s   |
     * |   1     |
     * | s   c   |
     * |       1 |
     */
    const auto rads = float(a) * 0.0174532925f;
    const auto c = std::cosf(rads);
    const auto s = std::sinf(rads);

    auto ret = Matrix4::identity();
    ret[0] = (c);
    ret[2] = (-s);
    ret[8] = (s);
    ret[10] = (c);
    return ret;
  }

  /**
   * Returns a rotation matrix about the z-axis.
   * @param  a [description]
   */
  auto rotateZ(T a) -> void
  {
    /**
     * Matrix4 Rotation Z
     * | c s     |
     * |-s c     |
     * |         |
     * |       1 |
     */
    float c = std::cosf(a);
    float s = std::sinf(a);

    auto t = Matrix4::identity();
    t[0] = c;
    t[1] = s;
    t[4] = -s;
    t[5] = c;

    (*this) = (*this) * t;
  }

  /**
   * Returns a transformation matrix.
   * @param  x     [description]
   * @param  y     [description]
   * @param  z     [description]
   * @param  angle [description]
   * @param  rx    [description]
   * @param  ry    [description]
   * @param  rz    [description]
   * @param  sx    [description]
   * @param  sy    [description]
   * @param  sz    [description]
   */
  static auto transform(T x, T y, T z, T a, T rx, T ry, T rz, T sx, T sy, T sz) -> Matrix4
  {
    auto m = Matrix4::identity();

    const auto rads = float(a) * 0.0174532925f;
    const auto c = std::cosf(rads);
    const auto s = std::sinf(rads);
    const auto ux = (x * x);
    const auto uy = (y * y);
    const auto uz = (z * z);

    m[0] = sx * (c + ux * (1 - c));
    m[1] = sy * ((y * x) * (1 - c) + z * s);
    m[2] = sz * ((z * x) * (1 - c) - y * s);

    m[4] = sx * ((x * y) * (1 - c) - z * s);
    m[5] = sy * (c + uy * (1 - c));
    m[6] = sz * ((z * y) * (1 - c) + x * s);

    m[8] = sx * ((x * z) * (1 - c) + y * s);
    m[9] = sy * ((y * z) * (1 - c) - x * s);
    ;
    m[10] = sz * (c + uz * (1 - c));

    m[12] = x * m[0] + y * m[4] + z * m[8];
    m[13] = x * m[1] + y * m[5] + z * m[9];
    m[14] = x * m[2] + y * m[6] + z * m[10];

    return m;
  }

  /**
   * [transform description]
   * @param  position [description]
   * @param  q        [description]
   * @param  scale    [description]
   */
  static auto transform(Vector3 position, Quaternion q, Vector3 scale) -> void
  {
    // TODO: ...
  }

  /**
   * Returns a perspective projection matrix.
   * @param  fovy   [description]
   * @param  aspect [description]
   * @param  near   [description]
   * @param  far    [description]
   */
  static auto perspective(T fovy, T aspect, T near, T far) -> Matrix4
  {
    auto ret = Matrix4::identity();
    float scale = (1.0f / std::tanf(fovy / 2.0f));
    float ratio = (scale / aspect);
    ret[0] = (ratio);
    ret[5] = (scale);
    ret[10] = (-(far) / (far - near));
    ret[11] = (-1.0f);
    ret[14] = (-(far * near) / (far - near));
    ret[15] = (0.0f);
    return ret;
  }

  /**
   * Returns an orthogonal projection matrix.
   * @param  left   [description]
   * @param  right  [description]
   * @param  bottom [description]
   * @param  top    [description]
   * @param  near   [description]
   * @param  far    [description]
   */
  static auto ortho(T left, T right, T bottom, T top, T near, T far) -> Matrix4
  {
    auto ret = Matrix4::identity();
    ret[0] = (2.0f / (right - left));
    ret[5] = (2.0f / (top - bottom));
    ret[10] = (-2.0f / (far - near));
    ret[12] = (-(right + left) / (right - left));
    ret[13] = (-(top + bottom) / (top - bottom));
    ret[14] = (-(far + near) / (far - near));
    return ret;
  }

  // protected variables
protected:
  /**
   * Element Representation
   * | e0 e4 e8  e12 |
   * | e1 e5 e9  e13 |
   * | e2 e6 e10 e14 |
   * | e3 e7 e11 e15 |
   */
  T e[16];
}; // matrix4

typedef Matrix4<float> Matrix4f;