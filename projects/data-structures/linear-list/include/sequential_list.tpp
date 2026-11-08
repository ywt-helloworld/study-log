#include <stdexcept>
#include <utility>
#include <new>

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
    data_(new T[other.capacity_]), capacity_(other.capacity_), length_(other.length_) {
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
    data_(other.data_), capacity_(other.capacity_), length_(other.length_) {
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
    if(newSize < length_) return false;
    try {
        T* newData_ = new T[newSize];
        std::copy_n(data_, length_, newData_);
        delete[] data_;
        data_ = newData_;
        newData_ = nullptr;
    }
    catch(std::bad_alloc& error) {
        return false;
    }
    capacity_ = newSize;
    return true;
}

template <typename T>
bool SeqList<T>::empty() const{
    return length_ == 0;
}

template <typename T>
bool SeqList<T>::full() const{
    return length_ == capacity_;
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
    if(i < 1 || i > length_ + 1) {
        return false;
    }
    else if(full()) {
        bool allocation = true;
        if(capacity() == 0) {
            allocation = reserve(4);
        }
        else {
            allocation = reserve(capacity_ * 2);
        }
        if(allocation = false) return false;
    }
    for(std::size_t j = length_; j >= i; --j) {
        data_[j] = data_[j - 1];
    }
    data_[i - 1] = std::move(x);
    ++length_;
    return true;
}

template <typename T>
bool SeqList<T>::remove(std::size_t i) {
    if(empty()) return false;
    if(i < 1 || i > length_) return false;
    for(std::size_t j = i; j < length_; ++j) {
        data_[j - 1] = data_[j];
    }
    --length_;
    return true;
}

template <typename T>
std::optional<std::size_t> SeqList<T>::find(const T& x) const {
    for(std::size_t i = 0; i < length_; ++i) {
        if(data_[i] == x) {
            return i + 1;
        }
    }
    return std::nullopt;
}
