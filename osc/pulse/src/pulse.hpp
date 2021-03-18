// Copyright 2021 Akiomi Kamakura

#include "userosc.h"
#include "utils/float_math.h"

#ifndef OSC_PULSE_SRC_PULSE_HPP_

#define OSC_PULSE_SRC_PULSE_HPP_

#define k_pulse_duty_lut_size (4)
const float pulse_duty_lut_f[k_pulse_duty_lut_size] = { 0.125f, 0.250f, 0.500f, 0.750f };

struct Pulse {
  enum {
    k_flags_none = 0,
    k_flag_reset = 1<<0,
  };

  struct State {
    float phase;
    uint8_t flags;

    State(void) :
      phase(0.f),
      flags(k_flags_none)
    {}
  };

  struct Params {
    float duty;
    float depth;

    Params(void) :
      duty(0.f),
      depth(0.f)
    {}

    void setDutyFromParamVal(const float valf) {
      const uint8_t pulse_duty_lut_idx =
        clipmaxf(valf * k_pulse_duty_lut_size, k_pulse_duty_lut_size - 1);
      duty = pulse_duty_lut_f[pulse_duty_lut_idx];
    }
  };

  Pulse(void) {
    init();
  }

  void init(void) {
    state = State();
    params = Params();
  }

  float signal(const float phase) {
    return phase < params.duty ? -1.f : 1.f;
  }

  float position(const float phase) {
    return signal(phase) < 0
      ? (phase / params.duty)
      : ((phase - params.duty) / (1 - params.duty));
  }

  float attenuation(const float phase) {
    return fastersinf(position(phase) * M_PI_2) * params.depth;
  }

  State  state;
  Params params;
};

#endif  // OSC_PULSE_SRC_PULSE_HPP_
