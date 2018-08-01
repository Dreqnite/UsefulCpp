#ifndef SORTCORE_H
#define SORTCORE_H

#include <cstring>
#include <type_traits>
#include <iostream>

///=============================================================================
///=============================================================================
enum class SortOrder
{
    ASC,
    DESC
};

///=============================================================================
///=============================================================================
template <typename T, size_t SIZE>
class SortingCore
{

public:
    ///=============================================================================
    ///=============================================================================
    SortingCore(T* inputArray)
    {
        static_assert(std::is_integral<T>::value, "Integral value is required.");
        std::memcpy(m_array, inputArray, SIZE * sizeof(T));
    }

    ///=============================================================================
    ///=============================================================================
    virtual ~SortingCore() {}

    ///=============================================================================
    ///=============================================================================
    virtual void sort(const SortOrder order = SortOrder::ASC) = 0;

    ///=============================================================================
    ///=============================================================================
    void print()
    {
        for (const auto i : m_array)
        {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }

protected:
    T m_array[SIZE];

    ///=============================================================================
    ///=============================================================================
    void swap(T& element1,
              T& element2)
    {
        T tmp{ std::move(element1) };
        element1 = std::move(element2);
        element2 = std::move(tmp);
    }

    ///=============================================================================
    ///=============================================================================
    const bool compare(const T element1,
                       const T element2,
                       const SortOrder order = SortOrder::ASC)
    {
        switch (order)
        {
        default:
        case SortOrder::ASC:
            return element1 > element2;
        case SortOrder::DESC:
            return element1 < element2;
        }
    }
};

#endif // SORTINGCORE_H
