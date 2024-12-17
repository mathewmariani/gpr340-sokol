#pragma once

// #include "graphics/graphics.h"

// struct Camera
// {
//   float x;
//   float y;
//   float a;
//   float z;

//   explicit Camera() : x(0.0f), y(0.0f), a(0.0f), z(1.0f) {}

//   void XYtoCamera(int *x, int *y)
//   {
//     *x -= this->x;
//     *y -= this->y;
//   }

//   void set_position(float x, float y)
//   {
//     this->x = x;
//     this->y = y;
//   }

//   void set_rotation(float a)
//   {
//     this->a = a;
//   }

//   void set_camera()
//   {
//     engine::graphics::push_transform();
//     engine::graphics::translate(x, y);
//     engine::graphics::rotate(a);
//     engine::graphics::scale(z, z);
//   }

//   void unset_camera()
//   {
//     engine::graphics::pop_transform();
//   }
// };