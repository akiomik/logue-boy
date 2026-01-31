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

#ifndef OSC_POKEGOLD_SRC_POKEGOLD_HPP_

#define OSC_POKEGOLD_SRC_POKEGOLD_HPP_

#define k_pokegold_wave_size (32)
#define k_pokegold_wave_center (7.5)
#define k_pokegold_wave_cnt (10)
#define k_pokegold_resolution_max (16)

const uint8_t pokegold_wave0[k_pokegold_wave_size] = {0,  2,  4,  6,  8,  10, 12, 14, 15, 15, 15,
                                                      14, 14, 13, 13, 12, 12, 11, 10, 9,  8,  7,
                                                      6,  5,  4,  4,  3,  3,  2,  2,  1,  1};

const uint8_t pokegold_wave1[k_pokegold_wave_size] = {0,  2,  4,  6,  8,  10, 12, 14, 14, 15, 15,
                                                      15, 15, 14, 14, 14, 13, 13, 12, 11, 10, 9,
                                                      8,  7,  6,  5,  4,  3,  2,  2,  1,  1};

const uint8_t pokegold_wave2[k_pokegold_wave_size] = {1,  3,  6,  9,  11, 13, 14, 14, 14, 14, 15,
                                                      15, 15, 15, 14, 13, 13, 14, 15, 15, 15, 15,
                                                      14, 14, 14, 14, 13, 11, 9,  6,  3,  1};

const uint8_t pokegold_wave3[k_pokegold_wave_size] = {0,  2,  4,  6,  8,  10, 12, 13, 14, 15, 15,
                                                      14, 13, 14, 15, 15, 14, 14, 13, 12, 11, 10,
                                                      9,  8,  7,  6,  5,  4,  3,  2,  1,  0};

const uint8_t pokegold_wave4[k_pokegold_wave_size] = {0,  1,  2,  3,  4, 5, 6,  7,  8,  10, 12,
                                                      13, 14, 14, 15, 7, 7, 15, 14, 14, 13, 12,
                                                      10, 8,  7,  6,  5, 4, 3,  2,  1,  0};

const uint8_t pokegold_wave5[k_pokegold_wave_size] = {0,  0,  1, 1, 2,  2,  3,  3,  4,  4,  3,
                                                      3,  2,  2, 1, 1,  15, 15, 14, 14, 12, 12,
                                                      10, 10, 8, 8, 10, 10, 12, 12, 14, 14};

const uint8_t pokegold_wave6[k_pokegold_wave_size] = {0,  2,  4, 6, 8, 10, 12, 14, 12, 11, 10,
                                                      9,  8,  7, 6, 5, 15, 15, 15, 14, 14, 13,
                                                      13, 12, 4, 4, 3, 3,  2,  2,  1,  1};

const uint8_t pokegold_wave7[k_pokegold_wave_size] = {12, 0,  10, 9,  8,  7, 15, 5,  15, 15, 15,
                                                      14, 14, 13, 13, 12, 4, 4,  3,  3,  2,  2,
                                                      15, 1,  0,  2,  4,  6, 8,  10, 12, 14};

const uint8_t pokegold_wave8[k_pokegold_wave_size] = {4,  4,  3,  3,  2,  2,  1, 15, 0,  0,  4,
                                                      6,  8,  10, 12, 14, 15, 8, 15, 14, 14, 13,
                                                      13, 12, 12, 11, 10, 9,  8, 7,  6,  5};

const uint8_t pokegold_wave9[k_pokegold_wave_size] = {1, 1, 0, 0, 0,  0,  0, 8,  0,  0,  1,
                                                      3, 5, 7, 9, 10, 11, 4, 11, 10, 10, 9,
                                                      9, 8, 8, 7, 6,  5,  4, 3,  2,  1};

const uint8_t* pokegold_waves[k_pokegold_wave_cnt] = {
    pokegold_wave0, pokegold_wave1, pokegold_wave2, pokegold_wave3, pokegold_wave4,
    pokegold_wave5, pokegold_wave6, pokegold_wave7, pokegold_wave8,
};

struct PokeGold {
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
    uint8_t wave_idx = 0;
    uint8_t resolution = 1;

    Params() = default;

    void set_wave_idx_from_param_val(const float valf) {
      wave_idx = clipmaxf(valf * k_pokegold_wave_cnt, k_pokegold_wave_cnt - 1);
    }

    void set_resolution_from_param_val(const float valf) {
      resolution = clipmaxf(valf * k_pokegold_resolution_max, k_pokegold_resolution_max - 1) + 1;
    }
  };

  PokeGold() { init(); }

  void init() {
    state = State();
    params = Params();
  }

  // returns value in [0, (resolution - 1) / resolution]
  float lerp_factor(const float phase) const {
    const uint32_t lerp_frame_idx = phase * k_pokegold_wave_size * params.resolution;
    return static_cast<float>(lerp_frame_idx % params.resolution) / params.resolution;
  }

  float signal(const float phase) const {
    const float p = phase - static_cast<uint32_t>(phase);  // [0, 1)
    const uint8_t* wave = pokegold_waves[params.wave_idx];
    const uint8_t frame_idx = p * k_pokegold_wave_size;
    const uint8_t next_frame_idx = (frame_idx + 1) % k_pokegold_wave_size;

    const float frame = linintf(lerp_factor(p), static_cast<float>(wave[frame_idx]),
                                static_cast<float>(wave[next_frame_idx]));

    return (frame - k_pokegold_wave_center) / k_pokegold_wave_center;
  }

  State state;
  Params params;
};

#endif  // OSC_POKEGOLD_SRC_POKEGOLD_HPP_
