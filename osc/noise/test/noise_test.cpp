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

#include "noise.hpp"

TEST(NoiseTest, SetIsShortFromParamVal) {
  Noise noise = Noise();

  noise.params.setIsShortFromParamVal(0.000f);
  EXPECT_TRUE(noise.params.is_short);

  noise.params.setIsShortFromParamVal(0.499f);
  EXPECT_TRUE(noise.params.is_short);

  noise.params.setIsShortFromParamVal(0.500f);
  EXPECT_FALSE(noise.params.is_short);

  noise.params.setIsShortFromParamVal(1.000f);
  EXPECT_FALSE(noise.params.is_short);
}

TEST(NoiseTest, SampleShort) {
  Noise noise = Noise();

  EXPECT_EQ(0, noise.sample(0x7fff));
  EXPECT_EQ(0, noise.sample(0x3fbf));
  EXPECT_EQ(0, noise.sample(0x1f9f));
  EXPECT_EQ(0, noise.sample(0x0f8f));
  EXPECT_EQ(0, noise.sample(0x0787));
  EXPECT_EQ(0, noise.sample(0x0383));
  EXPECT_EQ(1, noise.sample(0x0181));
  EXPECT_EQ(0, noise.sample(0x40c0));
  EXPECT_EQ(0, noise.sample(0x2020));
  EXPECT_EQ(0, noise.sample(0x1010));
  EXPECT_EQ(0, noise.sample(0x0808));
  EXPECT_EQ(0, noise.sample(0x0404));
  EXPECT_EQ(1, noise.sample(0x0202));
  EXPECT_EQ(1, noise.sample(0x4141));
  EXPECT_EQ(0, noise.sample(0x60e0));
  EXPECT_EQ(0, noise.sample(0x3030));
}

TEST(NoiseTest, SampleLong) {
  Noise noise = Noise();

  EXPECT_EQ(0, noise.sample(0x7fff));
  EXPECT_EQ(0, noise.sample(0x3fff));
  EXPECT_EQ(0, noise.sample(0x1fff));
  EXPECT_EQ(0, noise.sample(0x0fff));
  EXPECT_EQ(0, noise.sample(0x07ff));
  EXPECT_EQ(0, noise.sample(0x03ff));
  EXPECT_EQ(0, noise.sample(0x01ff));
  EXPECT_EQ(0, noise.sample(0x00ff));
  EXPECT_EQ(0, noise.sample(0x007f));
  EXPECT_EQ(0, noise.sample(0x003f));
  EXPECT_EQ(0, noise.sample(0x001f));
  EXPECT_EQ(0, noise.sample(0x000f));
  EXPECT_EQ(0, noise.sample(0x0007));
  EXPECT_EQ(0, noise.sample(0x0003));
  EXPECT_EQ(1, noise.sample(0x0001));
  EXPECT_EQ(0, noise.sample(0x4000));
}

TEST(NoiseTest, UpdatedRegisterShort) {
  Noise noise = Noise();
  noise.params.is_short = true;

  EXPECT_EQ(0x3fbf, noise.update_register(0x7fff));
  EXPECT_EQ(0x1f9f, noise.update_register(0x3fbf));
  EXPECT_EQ(0x0f8f, noise.update_register(0x1f9f));
  EXPECT_EQ(0x0787, noise.update_register(0x0f8f));
  EXPECT_EQ(0x0383, noise.update_register(0x0787));
  EXPECT_EQ(0x0181, noise.update_register(0x0383));
  EXPECT_EQ(0x40c0, noise.update_register(0x0181));
  EXPECT_EQ(0x2020, noise.update_register(0x40c0));
  EXPECT_EQ(0x1010, noise.update_register(0x2020));
  EXPECT_EQ(0x0808, noise.update_register(0x1010));
  EXPECT_EQ(0x0404, noise.update_register(0x0808));
  EXPECT_EQ(0x0202, noise.update_register(0x0404));
  EXPECT_EQ(0x4141, noise.update_register(0x0202));
  EXPECT_EQ(0x60e0, noise.update_register(0x4141));
  EXPECT_EQ(0x3030, noise.update_register(0x60e0));
  EXPECT_EQ(0x1818, noise.update_register(0x3030));
}

TEST(NoiseTest, UpdatedRegisterLong) {
  Noise noise = Noise();
  noise.params.is_short = false;

  EXPECT_EQ(0x3fff, noise.update_register(0x7fff));
  EXPECT_EQ(0x1fff, noise.update_register(0x3fff));
  EXPECT_EQ(0x0fff, noise.update_register(0x1fff));
  EXPECT_EQ(0x07ff, noise.update_register(0x0fff));
  EXPECT_EQ(0x03ff, noise.update_register(0x07ff));
  EXPECT_EQ(0x01ff, noise.update_register(0x03ff));
  EXPECT_EQ(0x00ff, noise.update_register(0x01ff));
  EXPECT_EQ(0x007f, noise.update_register(0x00ff));
  EXPECT_EQ(0x003f, noise.update_register(0x007f));
  EXPECT_EQ(0x001f, noise.update_register(0x003f));
  EXPECT_EQ(0x000f, noise.update_register(0x001f));
  EXPECT_EQ(0x0007, noise.update_register(0x000f));
  EXPECT_EQ(0x0003, noise.update_register(0x0007));
  EXPECT_EQ(0x0001, noise.update_register(0x0003));
  EXPECT_EQ(0x4000, noise.update_register(0x0001));
  EXPECT_EQ(0x2000, noise.update_register(0x4000));
}
