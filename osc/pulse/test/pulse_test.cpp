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

#include <gtest/gtest.h>

#include "pulse.hpp"

TEST(PulseTest, SetDutyFromParamVal) {
  Pulse pulse = Pulse();

  pulse.params.setDutyFromParamVal(0.000f);
  EXPECT_FLOAT_EQ(0.125f, pulse.params.duty);

  pulse.params.setDutyFromParamVal(0.249f);
  EXPECT_FLOAT_EQ(0.125f, pulse.params.duty);

  pulse.params.setDutyFromParamVal(0.250f);
  EXPECT_FLOAT_EQ(0.250f, pulse.params.duty);

  pulse.params.setDutyFromParamVal(0.499f);
  EXPECT_FLOAT_EQ(0.250f, pulse.params.duty);

  pulse.params.setDutyFromParamVal(0.500f);
  EXPECT_FLOAT_EQ(0.500f, pulse.params.duty);

  pulse.params.setDutyFromParamVal(0.749f);
  EXPECT_FLOAT_EQ(0.500f, pulse.params.duty);

  pulse.params.setDutyFromParamVal(0.750f);
  EXPECT_FLOAT_EQ(0.750f, pulse.params.duty);

  pulse.params.setDutyFromParamVal(1.000f);
  EXPECT_FLOAT_EQ(0.750f, pulse.params.duty);
}

TEST(PulseTest, Signal125) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[0];

  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.000f));
  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.124f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.125f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.250f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.500f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.750f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(1.000f));
}

TEST(PulseTest, Signal250) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[1];

  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.000f));
  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.249f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.250f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.500f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.750f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(1.000f));
}

TEST(PulseTest, Signal500) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[2];

  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.000f));
  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.250f));
  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.499f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.500f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.750f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(1.000f));
}

TEST(PulseTest, Signal750) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[3];

  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.000f));
  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.250f));
  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.500f));
  EXPECT_FLOAT_EQ(-1.f, pulse.signal(0.749f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(0.750f));
  EXPECT_FLOAT_EQ(1.f,  pulse.signal(1.000f));
}

TEST(PulseTest, Position125) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[0];

  EXPECT_FLOAT_EQ(0.0f, pulse.position(0.0000f));
  EXPECT_NEAR(1.0f,     pulse.position(0.1249f), 1e-3);
  EXPECT_FLOAT_EQ(0.0f, pulse.position(0.1250f));
  EXPECT_FLOAT_EQ(0.5f, pulse.position(0.5625f));
  EXPECT_FLOAT_EQ(1.0f, pulse.position(1.0000f));
}

TEST(PulseTest, Position250) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[1];

  EXPECT_FLOAT_EQ(0.0f, pulse.position(0.0000f));
  EXPECT_NEAR(1.0f,     pulse.position(0.2499f), 1e-3);
  EXPECT_FLOAT_EQ(0.0f, pulse.position(0.2500f));
  EXPECT_FLOAT_EQ(0.5f, pulse.position(0.6250f));
  EXPECT_FLOAT_EQ(1.0f, pulse.position(1.0000f));
}

TEST(PulseTest, Position500) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[2];

  EXPECT_FLOAT_EQ(0.0f, pulse.position(0.0000f));
  EXPECT_NEAR(1.0f,     pulse.position(0.4999f), 1e-3);
  EXPECT_FLOAT_EQ(0.0f, pulse.position(0.5000f));
  EXPECT_FLOAT_EQ(1.0f, pulse.position(1.0000f));
}

TEST(PulseTest, Position750) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[3];

  EXPECT_FLOAT_EQ(0.0f, pulse.position(0.0000f));
  EXPECT_FLOAT_EQ(0.5f, pulse.position(0.3750f));
  EXPECT_NEAR(1.0f,     pulse.position(0.7499f), 1e-3);
  EXPECT_FLOAT_EQ(0.0f, pulse.position(0.7500f));
  EXPECT_FLOAT_EQ(1.0f, pulse.position(1.0000f));
}

TEST(PulseTest, Attenuation125) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[0];

  pulse.params.depth = 1.f;
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.0000f));
  EXPECT_NEAR(1.0f,     pulse.attenuation(0.1249f), 1e-3);
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.1250f));
  EXPECT_FLOAT_EQ(1.0f, pulse.attenuation(1.0000f));

  pulse.params.depth = 0.f;
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.0000f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.1249f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.1250f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(1.0000f));
}

TEST(PulseTest, Attenuation250) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[1];

  pulse.params.depth = 1.f;
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.0000f));
  EXPECT_NEAR(1.0f,     pulse.attenuation(0.2499f), 1e-3);
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.2500f));
  EXPECT_FLOAT_EQ(1.0f, pulse.attenuation(1.0000f));

  pulse.params.depth = 0.f;
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.0000f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.2499f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.2500f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(1.0000f));
}

TEST(PulseTest, Attenuation500) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[2];

  pulse.params.depth = 1.f;
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.0000f));
  EXPECT_NEAR(1.0f,     pulse.attenuation(0.4999f), 1e-3);
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.5000f));
  EXPECT_FLOAT_EQ(1.0f, pulse.attenuation(1.0000f));

  pulse.params.depth = 0.f;
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.0000f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.4999f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.5000f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(1.0000f));
}

TEST(PulseTest, Attenuation750) {
  Pulse pulse = Pulse();
  pulse.params.duty = pulse_duty_lut_f[3];

  pulse.params.depth = 1.f;
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.0000f));
  EXPECT_NEAR(1.0f,     pulse.attenuation(0.7499f), 1e-3);
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.7500f));
  EXPECT_FLOAT_EQ(1.0f, pulse.attenuation(1.0000f));

  pulse.params.depth = 0.f;
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.0000f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.7499f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(0.7500f));
  EXPECT_FLOAT_EQ(0.0f, pulse.attenuation(1.0000f));
}
