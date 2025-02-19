#include "matrix.h"
#include <iostream>
#include <iomanip>



template <typename TupleT, std::size_t... Is>
std::ostream& printTupleImp(std::ostream& os, const TupleT& tp, std::index_sequence<Is...>) {
    size_t index = 0;
    auto printElem = [&index, &os](const auto& x) {
        if (index++ > 0) 
            os << ", ";
        os << x;
    };

    os << "(";
    (printElem(std::get<Is>(tp)), ...);
    os << ")";
    return os;
}

template <typename TupleT, std::size_t TupSize = std::tuple_size<TupleT>::value>
std::ostream& operator <<(std::ostream& os, const TupleT& tp) {
    return printTupleImp(os, tp, std::make_index_sequence<TupSize>{}); 
}

template <typename T, size_t N>
std::ostream& operator <<(std::ostream& os, const Matrix<T, N>& m) {
    for (const auto& tup : m)
    {
        std::cout << std::setw(2) << tup << std::endl;
    }
    return os;
}


template <typename T, size_t N>
void iterate(Matrix<T, N>& m)
{
    for (const auto& tup : m)
    {
        std::cout << std::setw(2) << tup << std::endl;
    }
}

