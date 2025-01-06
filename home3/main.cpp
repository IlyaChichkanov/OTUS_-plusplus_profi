#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <chrono>

#include "allocator.h"
#include "container.h"

using namespace std::chrono;


int fibbonachi(int n)
{
    if(n <= 1)
    {
        return 0;
    }
    if(n == 2)
    {
        return 1;
    }
    int prev_prev = 0;
    int prev = 1;
    int res = 0;
    for(size_t i = 0; i < n - 2; ++i)
    {
        res = prev_prev + prev;
        prev_prev = prev;
        prev = res;

    }
    return res;
}

template <typename Map>
void FillMap(Map& map, int n) {
    for (int i = 0; i <= n; ++i) {
        map[i] = fibbonachi(i);
    }
}

template <typename Map>
void PrintMap(const Map& map) {
    for (const auto & [k, v] : map) {
        std::cout << k << " " << v << std::endl;
    }
}

template <typename Container>
void FillContainer(Container & container, int n) {
    for (int i = 0; i < n; ++i)
    {
        container.push_back(fibbonachi(i));
    }

}

template <typename Container>
void EraseFromContainer(Container & container, int n) {
    for (int i = 0; i < n; ++i)
    {
        container.pop_back();
    }
}

template <typename Container>
void PrintContainer(const Container & container) {
    for (const auto & el : container)
    {
        std::cout << el << " ";
    }
}

int main() {

    // default map
    std::map<int, int> default_map;
    std::cout << "Default map" << std::endl;
    FillMap(default_map, 10);
    PrintMap(default_map);
    std::cout << std::endl;

    // map with custom allocator
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>, 11>> custom_allocator_map;
    std::cout << "Map with custom allocator" << std::endl;
    FillMap(custom_allocator_map, 10);
    PrintMap(custom_allocator_map);
    
    std::cout << std::endl;

    // CustomVector with std::allocator
    CustomVector<int> custom_vector_with_std_allocator;
    std::cout << "CustomVector with std::allocator" << std::endl;
    FillContainer(custom_vector_with_std_allocator, 10);
    PrintContainer(custom_vector_with_std_allocator);
    
    std::cout << std::endl;

    //MyVector with custom allocator
    CustomVector<int, CustomAllocator<int, 24>> custom_vector_with_custom_allocator;
    std::cout << "CustomVector with custom allocator" << std::endl;
    FillContainer(custom_vector_with_custom_allocator, 10);
    FillContainer(custom_vector_with_custom_allocator, 3);
    EraseFromContainer(custom_vector_with_custom_allocator, 3);
    PrintContainer(custom_vector_with_custom_allocator);

    return 0;
}   
