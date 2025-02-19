#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <cstddef>
#include <unordered_map>
#include <map>
#include <array>
#include <utility>
#include <type_traits>
#include <optional>
#include <functional>
#include <stdexcept>


template <typename T, 
        size_t dimention = 2>
class Matrix
{
public:
    explicit Matrix(T default_value)
    : default_value_(default_value){}
    Matrix(){}
    using Element =  Matrix<T, dimention - 1>;
    size_t size()
    {
        size_t accomulated_size = 0;
        for (auto& elem: storage_)
        {
            accomulated_size += elem.second.size();
        }
        return accomulated_size;
    }

    Element& operator[](const size_t idx) {
        if(storage_.count(idx))
        {
            return storage_[idx];
        }
        storage_[idx] = Element(default_value_);
        return storage_[idx];
    }

    // const Element& operator[](const size_t idx) const{
    //     if(storage_.count(idx))
    //     {
    //         return storage_[idx];
    //     }
    //     return Element(default_value_);
    // }

    class iterator {
    public:
        using value_type = Matrix;
        using pointer = Matrix *;

        iterator(Matrix& parent, size_t elem_num_) : parent_(parent), elem_num_(elem_num_) {}

        iterator operator++() {
            iterator i = *this;
            elem_num_++;
            return i;
        }

        decltype(auto)  operator*() { return parent_.get_element_by_id(elem_num_); }

        iterator operator=(const iterator& rhs) 
        {   
            parent_ = rhs.parent_;
            elem_num_ = rhs.elem_num_;
            return *this;
        }

        bool operator!=(const iterator& rhs) { return elem_num_ != rhs.elem_num_; }

    private:
        Matrix& parent_;
        size_t elem_num_;
    };

    iterator begin() {
        return iterator(*this, 0);
    }

    iterator end() {
        return iterator(*this, size());
    }

    iterator cbegin() const {
        return iterator(*this, 0);
    }

    iterator cend() const {
        return iterator(*this, size());
    }

    decltype(auto) get_element_by_id(size_t index)
    {   
        for(auto& [key, submatrix]: storage_)
        {
            size_t submatrix_size = submatrix.size();
            if(index < submatrix_size)
            {
                return std::tuple_cat(std::make_tuple(key), submatrix.get_element_by_id(index));
            }
            else
            {
                index -= submatrix_size;
            }
        }
        throw std::logic_error("unkown id");
    }

private:
    std::unordered_map<size_t, Element> storage_;
    T default_value_;

};

template <typename T>
class Matrix<T, 1>
{
public:
    explicit Matrix(T default_value)
    : default_value_(default_value)
    { }
    Matrix(){}
    Matrix(const Matrix&) = default;
    class Element {
    public:
        Element(T data_, T default_value, int id_, Matrix *matrix_ptr) :
                data_{data_}, default_value_(default_value), idx{id_}, matrix_ptr_(matrix_ptr) {}

        operator T() const {
            return data_;
        }

        Element& operator=(const T& rhs) {
            data_ = rhs;
            if (data_ != default_value_){
                matrix_ptr_->move_to_known(idx);
            }
            else{
                matrix_ptr_->move_to_unknown(idx);
            }
            return *this;
        }

        T item() const {
            return data_;
        }

        bool operator==(const T rhs) const {
            return data_ == rhs;
        }

        bool operator!=(const T rhs) const {
            return data_ != rhs;
        }

        bool operator==(const Element rhs) const {
            return data_ == rhs.data;
        }

        bool operator!=(const Element rhs) const {
            return data_ != rhs.data;
        }

    private:
        T data_;
        T default_value_;
        int idx;
        Matrix *matrix_ptr_;
    };
    
    Element& operator[](const int idx) {
        if (storage_.count(idx) == 0) {
            if (storage_temp_.count(idx) > 0)
                return *storage_temp_.at(idx);
            auto elem = std::make_shared<Element>(default_value_, default_value_, idx, this);
            storage_temp_.insert(std::make_pair(idx, elem));
            return *elem;
        }
        return *storage_.at(idx);
    }

    size_t size()
    {
        return storage_.size();
    }

    class iterator {
    public:
        using value_type = Matrix;
        using pointer = Matrix *;
        using difference_type = size_t;

        iterator(Matrix& parent, size_t elem_num_) : parent_(parent), elem_num_(elem_num_) {}

        iterator operator++() {
            iterator i = *this;
            elem_num_++;
            return i;
        }

        std::tuple<size_t, T>  operator*() { return parent_.get_element_by_id(elem_num_); }

        iterator operator=(const iterator& rhs) 
        {   
            parent_ = rhs.parent_;
            elem_num_ = rhs.elem_num_;
            return *this;
        }

        bool operator!=(const iterator& rhs) { return elem_num_ != rhs.elem_num_; }

    private:
        Matrix& parent_;
        size_t elem_num_;
    };

    iterator begin() {
        return iterator(*this, 0);
    }

    iterator end() {
        return iterator(*this, size());
    }

    iterator cbegin() const {
        return iterator(*this, 0);
    }

    iterator cend() const {
        return iterator(*this, size());
    }

    std::tuple<size_t, T> get_element_by_id(size_t id)
    {   
        size_t i = 0;
        for(auto& [key, value]: storage_)
        {
            if(i == id)
            {
                return std::make_tuple(key, value->item()) ;
            }
            i++;
        }
        throw std::logic_error("unkown id");
    }

    Matrix& operator=(const Matrix& other)
    {
        default_value_ = other.default_value_;
        storage_ = other.storage_;
        return *this;
    }

private:
    std::unordered_map<size_t, std::shared_ptr<Element>> storage_;
    T default_value_;
    std::unordered_map<size_t, std::shared_ptr<Element>> storage_temp_;

    void move_to_known(int idx) {
        if (storage_temp_.count(idx) > 0) {
            storage_.insert(std::make_pair(idx, storage_temp_.at(idx)));
            storage_temp_.erase(idx);
        }
    }

    void move_to_unknown(int idx) {
        if (storage_.count(idx) > 0) {
            storage_.erase(idx);
        }
        if (storage_temp_.count(idx) > 0) {
            storage_temp_.erase(idx);
        }
    }
};

#endif // MATRIX_H
