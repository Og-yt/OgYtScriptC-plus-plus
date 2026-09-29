#ifndef DIVISORFUNCTION_HPP
#define DIVISORFUNCTION_HPP

#include <cmath>
#include <vector>
#include <algorithm>
#include <cstddef>

class MYVECTOR
{
private:
    int *data_;
    std::size_t size_;
    std::size_t capacity_;

    void resize_capacity(std::size_t new_capacity)
    {
        int *new_data = new int[new_capacity];
        for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    MYVECTOR() : data_(nullptr), size_(0), capacity_(0) {}
    ~MYVECTOR()
    {
        delete[] data_;
    }
    void push_back(const int &value)
    {
        if (size_ >= capacity_)
        {
            std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            resize_capacity(new_capacity);
        }
        data_[size_] = value;
        ++size_;
    }
    void push_back_range(const int *begin_it, const int *end_it)
    {
        std::size_t additional_size = end_it - begin_it;
        if (additional_size == 0)
            return;

        if (size_ + additional_size > capacity_)
        {
            resize_capacity(size_ + additional_size);
        }

        for (const int *it = begin_it; it != end_it; ++it)
        {
            data_[size_] = *it;
            ++size_;
        }
    }

    const int *begin() const
    {
        return data_;
    }

    const int *end() const
    {
        return data_ + size_;
    }

    std::size_t size() const
    {
        return size_;
    }
};

namespace std {
    inline string to_string(const MYVECTOR& vec) {
        string result = "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            result += std::to_string(vec.begin()[i]) + (i == vec.size() - 1 ? "" : ", ");
        }
        result += "]";
        return result;
    }
}

#define __R_DIVISOR_FUNCTION_SIGMA_0__(N) [&]() {    \
    int COUNT = 0;                                   \
    for (int I = 1; std::pow(I,2) <= N; I++)         \
    {                                                \
        if (N % I == 0)                              \
        {                                            \
            COUNT++;                                 \
            if (std::pow(I,2) != N)                  \
            {                                        \
                COUNT++;                             \
            }                                        \
        }                                            \
    }                                                \
    return COUNT; }()

#define __R_DIVISOR_FUNCTION_SIGMA_1__(N) [&]() {       \
    long long SUM = 0;                                  \
    for (long long I = 1; std::pow(I,2) <= N; I++)      \
    {                                                   \
        if (N % I == 0)                                 \
        {                                               \
            SUM += I;                                   \
            if (std::pow(I,2) != N)                     \
            {                                           \
                SUM += (N / I);                         \
            }                                           \
        }                                               \
    }                                                   \
    return SUM; }()

#define __R_DIVISOR_FUNCTION_SORT_VER__(N) [&]() { \
    MYVECTOR DIVISORS;                            \
    for (long long I = 1; std::pow(I,2) <= N; I++) \
    {                                              \
        if (N % I == 0)                            \
        {                                          \
            DIVISORS.push_back(I);                 \
            if (std::pow(I,2) != N)                \
            {                                      \
                DIVISORS.push_back(N / I);         \
            }                                      \
        }                                          \
    }                                              \
    std::sort(const_cast<int*>(DIVISORS.begin()), const_cast<int*>(DIVISORS.end())); \
    return std::stoll(DIVISORS); }()

#endif // DIVISORFUNCTION_HPP