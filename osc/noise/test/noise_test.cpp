// Copyright 2021 Akiomi Kamakura

#include <gtest/gtest.h>

#include "noise.hpp"

TEST(NoiseTest, SetIsShortFromParamVal) {
  Noise noise = Noise();

  noise.params.setIsShortFromParamVal(0.000f);
  EXPECT_TRUE(noise.params.isShort);

  noise.params.setIsShortFromParamVal(0.499f);
  EXPECT_TRUE(noise.params.isShort);

  noise.params.setIsShortFromParamVal(0.500f);
  EXPECT_FALSE(noise.params.isShort);

  noise.params.setIsShortFromParamVal(1.000f);
  EXPECT_FALSE(noise.params.isShort);
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
  noise.params.isShort = true;

  EXPECT_EQ(0x3fbf, noise.updatedRegister(0x7fff));
  EXPECT_EQ(0x1f9f, noise.updatedRegister(0x3fbf));
  EXPECT_EQ(0x0f8f, noise.updatedRegister(0x1f9f));
  EXPECT_EQ(0x0787, noise.updatedRegister(0x0f8f));
  EXPECT_EQ(0x0383, noise.updatedRegister(0x0787));
  EXPECT_EQ(0x0181, noise.updatedRegister(0x0383));
  EXPECT_EQ(0x40c0, noise.updatedRegister(0x0181));
  EXPECT_EQ(0x2020, noise.updatedRegister(0x40c0));
  EXPECT_EQ(0x1010, noise.updatedRegister(0x2020));
  EXPECT_EQ(0x0808, noise.updatedRegister(0x1010));
  EXPECT_EQ(0x0404, noise.updatedRegister(0x0808));
  EXPECT_EQ(0x0202, noise.updatedRegister(0x0404));
  EXPECT_EQ(0x4141, noise.updatedRegister(0x0202));
  EXPECT_EQ(0x60e0, noise.updatedRegister(0x4141));
  EXPECT_EQ(0x3030, noise.updatedRegister(0x60e0));
  EXPECT_EQ(0x1818, noise.updatedRegister(0x3030));
}

TEST(NoiseTest, UpdatedRegisterLong) {
  Noise noise = Noise();
  noise.params.isShort = false;

  EXPECT_EQ(0x3fff, noise.updatedRegister(0x7fff));
  EXPECT_EQ(0x1fff, noise.updatedRegister(0x3fff));
  EXPECT_EQ(0x0fff, noise.updatedRegister(0x1fff));
  EXPECT_EQ(0x07ff, noise.updatedRegister(0x0fff));
  EXPECT_EQ(0x03ff, noise.updatedRegister(0x07ff));
  EXPECT_EQ(0x01ff, noise.updatedRegister(0x03ff));
  EXPECT_EQ(0x00ff, noise.updatedRegister(0x01ff));
  EXPECT_EQ(0x007f, noise.updatedRegister(0x00ff));
  EXPECT_EQ(0x003f, noise.updatedRegister(0x007f));
  EXPECT_EQ(0x001f, noise.updatedRegister(0x003f));
  EXPECT_EQ(0x000f, noise.updatedRegister(0x001f));
  EXPECT_EQ(0x0007, noise.updatedRegister(0x000f));
  EXPECT_EQ(0x0003, noise.updatedRegister(0x0007));
  EXPECT_EQ(0x0001, noise.updatedRegister(0x0003));
  EXPECT_EQ(0x4000, noise.updatedRegister(0x0001));
  EXPECT_EQ(0x2000, noise.updatedRegister(0x4000));
}
