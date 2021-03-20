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

#include "pokegold.hpp"

TEST(PokeGoldTest, SetWaveIdxFromParamVal) {
  PokeGold pokegold = PokeGold();

  pokegold.params.set_wave_idx_from_param_val(0.000f);
  EXPECT_EQ(0, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.099f);
  EXPECT_EQ(0, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.100f);
  EXPECT_EQ(1, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.199f);
  EXPECT_EQ(1, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.200f);
  EXPECT_EQ(2, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.299f);
  EXPECT_EQ(2, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.300f);
  EXPECT_EQ(3, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.399f);
  EXPECT_EQ(3, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.400f);
  EXPECT_EQ(4, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.499f);
  EXPECT_EQ(4, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.500f);
  EXPECT_EQ(5, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.599f);
  EXPECT_EQ(5, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.600f);
  EXPECT_EQ(6, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.699f);
  EXPECT_EQ(6, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.700f);
  EXPECT_EQ(7, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.799f);
  EXPECT_EQ(7, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.800f);
  EXPECT_EQ(8, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.899f);
  EXPECT_EQ(8, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(0.900f);
  EXPECT_EQ(9, pokegold.params.wave_idx);

  pokegold.params.set_wave_idx_from_param_val(1.000f);
  EXPECT_EQ(9, pokegold.params.wave_idx);
}

TEST(PokeGoldTest, SetScaleFromParamVal) {
  PokeGold pokegold = PokeGold();

  pokegold.params.set_scale_from_param_val(0.0000f);
  EXPECT_EQ(1, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.0625f);
  EXPECT_EQ(2, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.1250f);
  EXPECT_EQ(3, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.1875f);
  EXPECT_EQ(4, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.2500f);
  EXPECT_EQ(5, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.3125f);
  EXPECT_EQ(6, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.3750f);
  EXPECT_EQ(7, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.4375f);
  EXPECT_EQ(8, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.5000f);
  EXPECT_EQ(9, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.5625f);
  EXPECT_EQ(10, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.6250f);
  EXPECT_EQ(11, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.6875f);
  EXPECT_EQ(12, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.7500f);
  EXPECT_EQ(13, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.8125f);
  EXPECT_EQ(14, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.8750);
  EXPECT_EQ(15, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(0.9375);
  EXPECT_EQ(16, pokegold.params.scale);

  pokegold.params.set_scale_from_param_val(1.000f);
  EXPECT_EQ(16, pokegold.params.scale);
}

TEST(PokeGoldTest, LerpFactor1) {
  PokeGold pokegold = PokeGold();
  pokegold.params.scale = 1;

  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.0000000f));  // idx=0
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.1250000f));  // idx=4
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.1666667f));  // idx=5.334
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.2500000f));  // idx=8
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.3333334f));  // idx=10.667
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.3750000f));  // idx=12
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.5000000f));  // idx=16
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.6250000f));  // idx=20
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.6666667f));  // idx=21.334
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.7500000f));  // idx=24
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.8333334f));  // idx=26.667
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.8750000f));  // idx=28
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(1.0000000f));  // idx=0
}

TEST(PokeGoldTest, LerpFactor2) {
  PokeGold pokegold = PokeGold();
  pokegold.params.scale = 2;

  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.0000000f));  // idx=0
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.1250000f));  // idx=4
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.1666667f));  // idx=5.334
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.2500000f));  // idx=8
  EXPECT_FLOAT_EQ(0.5000000f, pokegold.lerp_factor(0.3333334f));  // idx=10.667
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.3750000f));  // idx=12
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.5000000f));  // idx=16
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.6250000f));  // idx=20
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.6666667f));  // idx=21.334
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.7500000f));  // idx=24
  EXPECT_FLOAT_EQ(0.5000000f, pokegold.lerp_factor(0.8333334f));  // idx=26.667
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.8750000f));  // idx=28
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(1.0000000f));  // idx=0
}

TEST(PokeGoldTest, LerpFactor3) {
  PokeGold pokegold = PokeGold();
  pokegold.params.scale = 3;

  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.0000000f));  // idx=0
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.1250000f));  // idx=4
  EXPECT_FLOAT_EQ(0.3333334f, pokegold.lerp_factor(0.1666667f));  // idx=5.334
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.2500000f));  // idx=8
  EXPECT_FLOAT_EQ(0.6666667f, pokegold.lerp_factor(0.3333334f));  // idx=10.667
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.3750000f));  // idx=12
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.5000000f));  // idx=16
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.6250000f));  // idx=20
  EXPECT_FLOAT_EQ(0.3333334f, pokegold.lerp_factor(0.6666667f));  // idx=21.334
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.7500000f));  // idx=24
  EXPECT_FLOAT_EQ(0.6666667f, pokegold.lerp_factor(0.8333334f));  // idx=26.667
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(0.8750000f));  // idx=28
  EXPECT_FLOAT_EQ(0.0000000f, pokegold.lerp_factor(1.0000000f));  // idx=0
}

TEST(PokeGoldTest, SignalWave2Scale1) {
  PokeGold pokegold = PokeGold();
  pokegold.params.wave_idx = 2;
  pokegold.params.scale = 1;

  EXPECT_FLOAT_EQ(-0.8666667f, pokegold.signal(0.0000000f));  // idx=0
  EXPECT_FLOAT_EQ(0.4666667f,  pokegold.signal(0.1250000f));  // idx=4
  EXPECT_FLOAT_EQ(0.7333334f,  pokegold.signal(0.1666667f));  // idx=5.334
  EXPECT_FLOAT_EQ(0.8666667f,  pokegold.signal(0.2500000f));  // idx=8
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.3333334f));  // idx=10.667
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.3750000f));  // idx=12
  EXPECT_FLOAT_EQ(0.7333334f,  pokegold.signal(0.5000000f));  // idx=16
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.6250000f));  // idx=20
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.6666667f));  // idx=21.334
  EXPECT_FLOAT_EQ(0.8666667f,  pokegold.signal(0.7500000f));  // idx=24
  EXPECT_FLOAT_EQ(0.7333334f,  pokegold.signal(0.8333334f));  // idx=26.667
  EXPECT_FLOAT_EQ(0.2000000f,  pokegold.signal(0.8750000f));  // idx=28
  EXPECT_FLOAT_EQ(-0.8666667f, pokegold.signal(1.0000000f));  // idx=0
}

TEST(PokeGoldTest, SignalWave2Scale2) {
  PokeGold pokegold = PokeGold();
  pokegold.params.wave_idx = 2;
  pokegold.params.scale = 2;

  EXPECT_FLOAT_EQ(-0.8666667f, pokegold.signal(0.0000000f));  // idx=0
  EXPECT_FLOAT_EQ(0.4666667f,  pokegold.signal(0.1250000f));  // idx=4
  EXPECT_FLOAT_EQ(0.7333334f,  pokegold.signal(0.1666667f));  // idx=5.334
  EXPECT_FLOAT_EQ(0.8666667f,  pokegold.signal(0.2500000f));  // idx=8
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.3333334f));  // idx=10.667
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.3750000f));  // idx=12
  EXPECT_FLOAT_EQ(0.7333334f,  pokegold.signal(0.5000000f));  // idx=16
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.6250000f));  // idx=20
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.6666667f));  // idx=21.334
  EXPECT_FLOAT_EQ(0.8666667f,  pokegold.signal(0.7500000f));  // idx=24
  EXPECT_FLOAT_EQ(0.6000000f,  pokegold.signal(0.8333334f));  // idx=26.667
  EXPECT_FLOAT_EQ(0.2000000f,  pokegold.signal(0.8750000f));  // idx=28
  EXPECT_FLOAT_EQ(-0.8666667f, pokegold.signal(1.0000000f));  // idx=0
}

TEST(PokeGoldTest, SignalWave2Scale3) {
  PokeGold pokegold = PokeGold();
  pokegold.params.wave_idx = 2;
  pokegold.params.scale = 3;

  EXPECT_FLOAT_EQ(-0.8666667f, pokegold.signal(0.0000000f));  // idx=0
  EXPECT_FLOAT_EQ(0.4666667f,  pokegold.signal(0.1250000f));  // idx=4
  EXPECT_FLOAT_EQ(0.7777778f,  pokegold.signal(0.1666667f));  // idx=5.334
  EXPECT_FLOAT_EQ(0.8666667f,  pokegold.signal(0.2500000f));  // idx=8
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.3333334f));  // idx=10.667
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.3750000f));  // idx=12
  EXPECT_FLOAT_EQ(0.7333334f,  pokegold.signal(0.5000000f));  // idx=16
  EXPECT_FLOAT_EQ(1.0000000f,  pokegold.signal(0.6250000f));  // idx=20
  EXPECT_FLOAT_EQ(0.9555556f,  pokegold.signal(0.6666667f));  // idx=21.334
  EXPECT_FLOAT_EQ(0.8666667f,  pokegold.signal(0.7500000f));  // idx=24
  EXPECT_FLOAT_EQ(0.5555556f,  pokegold.signal(0.8333334f));  // idx=26.667
  EXPECT_FLOAT_EQ(0.2000000f,  pokegold.signal(0.8750000f));  // idx=28
  EXPECT_FLOAT_EQ(-0.8666667f, pokegold.signal(1.0000000f));  // idx=0
}
