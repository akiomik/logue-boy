// Copyright 2021 Akiomi Kamakura
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef LIBS_LOGUE_SDK_STUB_PLATFORM_MINILOGUE_XD_INC_UTILS_FLOAT_MATH_H_

#define LIBS_LOGUE_SDK_STUB_PLATFORM_MINILOGUE_XD_INC_UTILS_FLOAT_MATH_H_

#define _USE_MATH_DEFINES
#include <math.h>

float si_roundf(const float x) {
  return roundf(x);
}

float clipmaxf(const float x, const float m) {
  return fminf(x, m);
}

float fastersinf(const float x) {
  return sinf(x);
}

float linintf(const float fr, const float x0, const float x1) {
  return x0 + (x1 - x0) * fr;
}

#endif  // LIBS_LOGUE_SDK_STUB_PLATFORM_MINILOGUE_XD_INC_UTILS_FLOAT_MATH_H_
