#pragma once

#include <stack>
#include <vector>
#include <queue>

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <array>
#include <stdexcept>
#include <cassert>
#include <memory>


template <typename T, std::size_t max_size>
struct CustomAllocator {
    using value_type = T;

    CustomAllocator() = default;

    template <typename U>
    explicit CustomAllocator(const CustomAllocator<U, max_size>&) {}

    template<class U>
    struct rebind { 
        using other = CustomAllocator<U, max_size>; 
    };

    template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		new (p) U(std::forward<Args>(args)...);
	};

    template <typename U>
	void destroy(U *p) {
		p->~U();
	}

    T * allocate(size_t n)
    {
        //std::cout<<"allocate "<<n<<" "<<allocated_amount<<"\n";
        if (allocated_amount + n > max_size)
        {
            std::cout<<allocated_amount + n<<"\n";
            throw std::invalid_argument("CustomAllocator::allocate() memoty exeeded");
        }
		auto p = std::malloc(n * sizeof(T));
		if (!p)
        {
            throw std::bad_alloc();
        }
        allocated_amount += n;
		return reinterpret_cast<T *>(p);
    }

    void deallocate(T * p, size_t n)
    {
        if (n > max_size)
            throw std::invalid_argument("MemoryPool::deallocate(), bad `n'");

        allocated_amount -= n;
        std::free(p);
    }
private:
    size_t allocated_amount{0};
};