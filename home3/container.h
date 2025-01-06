#include <memory>
#include <iostream>

#include "allocator.h"

template <typename T, typename Allocator = std::allocator<T>>
class CustomVector {
public:
    CustomVector()
        : capacity_{1}
        , size_{0}
        , data_{allocator_.allocate(capacity_)}
    {}

    ~CustomVector() {
        for (size_t i = 0; i < size_; ++i) {
            allocator_.destroy(&data_[i]);
        }
    }
    
    void push_back(const T & elem) {
        if (size_ == capacity_) {
            //std::cerr << "realocate memory "<<capacity_<<"\n";
            size_t capacity_new = 2*capacity_;
            T * data_copy = allocator_.allocate(capacity_new);
            //std::cerr << "copy data\n";
            std::copy(data_, data_ + capacity_, data_copy);
            //std::cerr << "deallocate\n";
            allocator_.deallocate(data_, capacity_);
            data_ = data_copy;
            capacity_ = capacity_new;
        }
        allocator_.construct(&data_[size_], elem);
        size_++;
    }

    void pop_back() {
        if (size_ == 0) {
            std::cerr << "Pop with 0 size";
        }
        else {
            allocator_.destroy(&data_[size_]);
            size_--;
        }
    }

    T const * begin() const {
        return data_;
    }

    T const * end() const {
        return data_ + size_;
    }

private:
    Allocator allocator_;
    size_t capacity_;
    size_t size_;
    T * data_;
};