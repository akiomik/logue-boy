// Copyright 2021 Akiomi Kamakura

#ifndef LIBS_LOGUE_SDK_STUB_PLATFORM_MINILOGUE_XD_INC_UTILS_FLOAT_MATH_H_

#define LIBS_LOGUE_SDK_STUB_PLATFORM_MINILOGUE_XD_INC_UTILS_FLOAT_MATH_H_

#define _USE_MATH_DEFINES
#include <math.h>

float clipmaxf(const float x, const float m) {
  return fminf(x, m);
}

float fastersinf(const float x) {
  return sinf(x);
}

#endif  // LIBS_LOGUE_SDK_STUB_PLATFORM_MINILOGUE_XD_INC_UTILS_FLOAT_MATH_H_
