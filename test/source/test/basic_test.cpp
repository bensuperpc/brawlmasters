#include <string>

#include "gtest/gtest.h"

TEST(Basic, Base1) {
  EXPECT_EQ(true, true);
  EXPECT_EQ(false, false);
}

auto main(int argc, char **argv) -> int {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
