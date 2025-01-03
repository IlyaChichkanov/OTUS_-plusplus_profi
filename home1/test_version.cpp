#include <gtest/gtest.h>
#include "lib.h"



TEST(test_version, test_valid_version) {
    EXPECT_EQ(true, build_version() > 0);
}