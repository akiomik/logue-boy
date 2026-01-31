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

#include "float_math.h"
#include "userosc.h"

#include "pulse.hpp"

static Pulse s_pulse;

void OSC_INIT(uint32_t platform, uint32_t api) {
  (void)platform;
  (void)api;
}

void OSC_CYCLE(const user_osc_param_t* const params, int32_t* yn, const uint32_t frames) {
  Pulse::State& s = s_pulse.state;
  const Pulse::Params& p = s_pulse.params;

  const uint8_t flags = s.flags;
  s.flags = Pulse::k_flags_none;

  const float w0 = osc_w0f_for_note((params->pitch) >> 8, params->pitch & 0xFF);
  float phase = ((flags & Pulse::k_flag_reset) != 0) ? 0.f : s.phase;

  const float duty = p.duty;
  const float depth = p.depth;

  q31_t* __restrict y = reinterpret_cast<q31_t*>(yn);
  const q31_t* y_e = y + frames;

  for (; y != y_e;) {
    float sig = s_pulse.signal(phase);
    sig *= 1.f - s_pulse.attenuation(phase);

    *(y++) = f32_to_q31(sig);

    phase += w0;
    phase -= static_cast<uint32_t>(phase);
  }

  s.phase = phase;
}

void OSC_NOTEON(const user_osc_param_t* const params) {
  s_pulse.state.flags |= Pulse::k_flag_reset;
}

void OSC_NOTEOFF(const user_osc_param_t* const params) {
  (void)params;
}

void OSC_PARAM(uint16_t index, uint16_t value) {
  const float valf = param_val_to_f32(value);

  switch (index) {
    case k_user_osc_param_id1:
    case k_user_osc_param_id2:
    case k_user_osc_param_id3:
    case k_user_osc_param_id4:
    case k_user_osc_param_id5:
    case k_user_osc_param_id6:
      break;
    case k_user_osc_param_shape:
      s_pulse.params.set_duty_from_param_val(valf);
      break;
    case k_user_osc_param_shiftshape:
      s_pulse.params.depth = valf;
      break;
    default:
      break;
  }
}
