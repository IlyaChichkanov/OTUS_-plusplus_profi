#include "matrix.h"
#include "print.h"
#include <gtest/gtest.h>

#include <vector>
#include <unordered_map>

#include <iostream>



TEST(MatrixIndexing, 2D)
{
    Matrix<int, 2> m(5);
    m[1][1] = m[0][2] = 2;
    m[0][2] = m[100][100] = m[1][1] = 3;
    m[30][45] = (m[1][10] = 8) = 2;
    m[2][2] = 10;
    EXPECT_EQ(m[1][1], 3);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[100][100], 3);
    EXPECT_EQ(m[1][10], 2);
    EXPECT_EQ(m[30][45], 2);
    EXPECT_EQ(m[2][2], 10);
   // iterate(m);
}


TEST(MatrixGeneral, 2D)
{
    Matrix<int, 2> m(0);
    std::vector<std::vector<int>> v(10, std::vector<int>(10));
    for (std::size_t i = 0; i < 10; ++i)
    {
        v[i][i] = m[i][i] = i;
        v[i][9 - i] = m[i][9 - i] = 9 - i;
    }

    for (std::size_t i = 0; i < 10; ++i)
    {
        for (std::size_t j = 0; j < 10; ++j)
        {
            EXPECT_EQ(v[i][j], m[i][j]);
        }
    }
    // iterate(m);
    // std::cout << m.size() <<"\n";
    EXPECT_EQ(m.size(), 18);
}

TEST(MatrixGeneral, 3D)
{
    Matrix<int, 3> m(0);
    m[1][2][3] = 1;
    m[2][0][4] = 2;
    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(m[1][2][3], 1);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout<<"Tests";
    return RUN_ALL_TESTS();
}
