// Copyright 2021 Akiomi Kamakura

#include "float_math.h"
#include "userosc.h"

typedef struct State {
  float phase;
  float duty;
  float depth;
  uint8_t flags;
} State;

enum {
  k_flags_none = 0,
  k_flag_reset = 1<<0,
};

#define k_pulse_duty_lut_size (4)
const float pulse_duty_lut_f[k_pulse_duty_lut_size] = { 0.125f, 0.250f, 0.500f, 0.750f };

static State s_state;

void OSC_INIT(uint32_t platform, uint32_t api) {
  s_state.phase = 0.f;
  s_state.duty  = 0.f;
  s_state.depth = 0.f;
  s_state.flags = k_flags_none;
}

void OSC_CYCLE(const user_osc_param_t * const params,
               int32_t *yn,
               const uint32_t frames) {
  const uint8_t flags = s_state.flags;
  s_state.flags = k_flags_none;

  const float w0 = osc_w0f_for_note((params->pitch)>>8, params->pitch & 0xFF);
  float phase = (flags & k_flag_reset) ? 0.f : s_state.phase;

  const float duty = s_state.duty;
  const float depth = s_state.depth;

  q31_t * __restrict y = reinterpret_cast<q31_t *>(yn);
  const q31_t * y_e = y + frames;

  for (; y != y_e; ) {
    float sig = phase < duty ? -1.f : 1.f;
    const float position = sig < 0 ? (phase / duty) : ((phase - duty) / (1 - duty));  // [0, 1]
    const float attenuation = 1.f - fastersinf(position * M_PI_2) * depth;  // [0, 1]
    sig *= attenuation;

    *(y++) = f32_to_q31(sig);

    phase += w0;
    phase -= (uint32_t)phase;
  }

  s_state.phase = phase;
}

void OSC_NOTEON(const user_osc_param_t * const params) {
  s_state.flags |= k_flag_reset;
}

void OSC_NOTEOFF(const user_osc_param_t * const params) {
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
    {
      const uint8_t pulse_duty_lut_idx =
        clipmaxf(valf * k_pulse_duty_lut_size, k_pulse_duty_lut_size - 1);
      s_state.duty = pulse_duty_lut_f[pulse_duty_lut_idx];
    }
    break;
  case k_user_osc_param_shiftshape:
    s_state.depth = valf;
    break;
  default:
    break;
  }
}
