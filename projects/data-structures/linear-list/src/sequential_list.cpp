#include "include/sequential_list.hpp"
#include <algorithm>
#include <utility>
#include <memory>

template <typename T>
SeqList<T>::SeqList() : 
    data_(nullptr), capacity_(0), length_(0) {}

template <typename T>
SeqList<T>::SeqList(std::size_t maxSize) :
    data_(new T[maxSize]), capacity_(maxSize), length_(0) {}

template <typename T>
SeqList<T>::~SeqList() {
    delete[] data_;
}

template <typename T>
SeqList<T>::SeqList(const SeqList<T>& other) :
    data_(new T[other.capacity_]), capacity_(other.capacity), length_(other.length) {
    std::copy_n(other.data_, other.length_, data_);
}

template <typename T>
SeqList<T>& SeqList<T>::operator=(SeqList<T> other) {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(length_, other.length_);
    return *this;
}

template <typename T>
SeqList<T>::SeqList(SeqList<T>&& other) noexcept:
    data_(other.data_), capacity_(other.capacity), length_(other.length) {
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.length_ = 0;
}

template <typename T>
std::size_t SeqList<T>::capacity() const{
    return capacity_;
}

template <typename T>
std::size_t SeqList<T>::length() const{
    return length_;
}

template <typename T>
bool SeqList<T>::reserve(std::size_t newSize) {
    try {
        T* newData_ = new T[newSize];
    }
    catch(std::out_of_range& error) {
        return false;
    }
    std::copy_n(data_, length, newData_);
    capacity_ = newSize;
    return true;
}

template <typename T>
bool SeqList<T>::empty() const{
    return length == 0;
}

template <typename T>
bool SeqList<T>::full() const{
    return length == capacity();
}

template <typename T>
const T& SeqList<T>::operator[](std::size_t i) const{
    return data_[i - 1];
}

template <typename T>
T& SeqList<T>::operator[](std::size_t i) {
    return data_[i - 1];
}

template <typename T>
bool SeqList<T>::insert(std::size_t i, T x) {
    if(i < 1 || i > length) {
        return false;
    }
    else if(full()) {
        reserve(capacity_ * 2);
    }
    for(std::size_t j = length; j >= i; --j) {
        data_[j] = data_[j - 1];
    }
    data_[i - 1] = std::move(x);
    return true;
}

template <typename T>
bool SeqList<T>::remove(std::size_t i) {
    for(std::size_t j = i; j < length; ++j) {
        data_[j - 1] = data_[j];
    }
    return true;
}

template <typename T>
std::optional<std::size_t> SeqList<T>::find(const T& x) const {
    for(std::size_t i = 0; i < length; ++i) {
        if(data_[i] == x) {
            return i + 1;
        }
    }
    return std::nullopt;
}