#include "gtest/gtest.h"
#include "../../src/Utils/BitArray.h"

TEST(BitArray, BasicFunctionality) {
  auto bitArray = ColoringElements::Utils::BitArray();
  // color 0 is default color for unvisited or uncollor vertex
  EXPECT_EQ(bitArray.findFirstFalse(), 1);
  bitArray.setBit(1);
  EXPECT_EQ(bitArray.findFirstFalse(), 2);
  bitArray.Clear();
  EXPECT_EQ(bitArray.findFirstFalse(), 1);
  const uint MISSING_COLOR = 6;
  for (auto currentColor = 1; currentColor <= 12; ++currentColor) {
    if (currentColor == MISSING_COLOR) continue;
    bitArray.setBit(currentColor);
  }
  EXPECT_EQ(bitArray.findFirstFalse(), MISSING_COLOR);
}
