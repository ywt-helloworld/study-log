#pragma once

#include <cstddef>  
#include <optional>
#include <iostream>

#define MAX_SIZE 100
// 实现一个顺序表（Sequential List）

template <typename T>
class SeqList {
private:
    T* data_;          // 存储顺序表元素的数组
    std::size_t length_;    // 顺序表的当前长度
    std::size_t capacity_;     // 顺序表当前的容量
public:
    // Rule of five
    SeqList();
    SeqList(std::size_t maxSize);
    ~SeqList();
    SeqList(const SeqList<T>& other);
    SeqList<T>& operator=(SeqList<T> other);
    SeqList(SeqList<T>&& other) noexcept;

    // 基本操作
    std::size_t capacity() const;
    std::size_t length() const;
    bool reserve(std::size_t newSize);
    const T& operator[](std::size_t i) const;
    T& operator[](std::size_t i);
    bool insert(std::size_t i, T x);
    bool remove(std::size_t i);
    std::optional<std::size_t> find(const T& x) const;
    bool empty() const;
    bool full() const;
};