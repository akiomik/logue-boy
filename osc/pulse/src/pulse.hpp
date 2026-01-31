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

#ifndef OSC_PULSE_SRC_PULSE_HPP_

#define OSC_PULSE_SRC_PULSE_HPP_

#define k_pulse_duty_lut_size (4)
const float pulse_duty_lut_f[k_pulse_duty_lut_size] = {0.125f, 0.250f, 0.500f, 0.750f};

struct Pulse {
  enum {
    k_flags_none = 0,
    k_flag_reset = 1 << 0,
  };

  struct State {
    float phase = 0.f;
    uint8_t flags = k_flags_none;

    State() = default;
  };

  struct Params {
    float duty = 0.f;
    float depth = 0.f;

    Params() = default;

    void set_duty_from_param_val(const float valf) {
      const uint8_t pulse_duty_lut_idx =
          clipmaxf(valf * k_pulse_duty_lut_size, k_pulse_duty_lut_size - 1);
      duty = pulse_duty_lut_f[pulse_duty_lut_idx];
    }
  };

  Pulse() { init(); }

  void init() {
    state = State();
    params = Params();
  }

  float signal(const float phase) const { return phase < params.duty ? -1.f : 1.f; }

  float position(const float phase) const {
    return signal(phase) < 0 ? (phase / params.duty) : ((phase - params.duty) / (1 - params.duty));
  }

  float attenuation(const float phase) const {
    return fastersinf(position(phase) * M_PI_2) * params.depth;
  }

  State state;
  Params params;
};

#endif  // OSC_PULSE_SRC_PULSE_HPP_
