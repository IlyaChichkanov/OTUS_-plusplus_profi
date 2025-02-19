#include "matrix.h"
#include "print.h"
#include <iostream>
#include <iomanip>


int main()
{

    
    Matrix<int, 1> matrix1d(0);
    matrix1d[2] = 3;
    matrix1d[5] = 8;
    
   std::cout << "size = " << matrix1d.size() << std::endl;
   iterate(matrix1d);
   //std::cout << matrix1d;

    Matrix<int, 2> matrix2d(0);
    for (std::size_t i = 0; i < 10; ++i)
    {
        matrix2d[i][i] = i;
        matrix2d[i][9 - i] = 9 - i;
    }

    for (std::size_t i = 1; i <= 8; ++i)
    {
        for (std::size_t j = 1; j <= 8; ++j)
            std::cout << matrix2d[i][j] << ' ';
        std::cout << '\n';
    }

    Matrix<int, 2> Matrix2d(0);
    Matrix2d[1][2] = 3;
    Matrix2d[1][4] = 8;
    Matrix2d[3][6] = 3;
    iterate(Matrix2d);
}

