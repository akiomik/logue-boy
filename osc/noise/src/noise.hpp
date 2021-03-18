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

#include "userosc.h"
#include "utils/float_math.h"

#ifndef OSC_NOISE_SRC_NOISE_HPP_

#define OSC_NOISE_SRC_NOISE_HPP_

struct Noise {
  enum {
    k_flags_none = 0,
    k_flag_reset = 1<<0,
  };

  struct State {
    float phase;
    uint16_t reg;
    uint8_t flags;

    State(void) :
      phase(0.f),
      reg(0),
      flags(k_flags_none)
    {}
  };

  struct Params {
    bool isShort;

    Params(void) :
      isShort(true)
    {}

    void setIsShortFromParamVal(const float valf) {
      isShort = valf < 0.5f;
    }
  };

  Noise(void) {
    init();
  }

  void init(void) {
    state = State();
    params = Params();
  }

  uint8_t sample(const uint16_t reg) {
    const uint8_t prevLsb = reg & 1;
    const uint8_t newLsb = (reg >> 1) & 1;
    return prevLsb ^ newLsb;
  }

  uint16_t updatedRegister(const uint16_t reg) {
    const uint8_t output = sample(reg);
    uint16_t updated = reg >> 1;

    updated = (0x3fff & updated) | (output << 14);
    if (params.isShort) {
      updated = (0x7fbf & updated) | (output << 6);
    }

    return updated;
  }

  State  state;
  Params params;
};

#endif  // OSC_NOISE_SRC_NOISE_HPP_
