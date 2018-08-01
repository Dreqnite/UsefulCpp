#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "..\SortingCore.h"

///=============================================================================
/// Simple implementation of "Quick Sort".
/// 
/// Example of usage:
/// constexpr size_t arrSize = 20;
/// int inputArray[arrSize]{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 5, ... };
/// QuickSort<int, arrSize> qSort(inputArray);
/// qSort.sort(SortOrder::DESC);
/// qSort.print();
/// qSort.sort(SortOrder::ASC);
/// qSort.print();
///=============================================================================
template <typename T, size_t SIZE>
class QuickSort : public SortingCore<T, SIZE>
{
public:
    ///=============================================================================
    ///=============================================================================
    QuickSort(T* inputArray)
        : SortingCore<T, SIZE>(inputArray)
    {}

    ///=============================================================================
    ///=============================================================================
    ~QuickSort() {}

    ///=============================================================================
    ///=============================================================================
    void sort(const SortOrder order = SortOrder::ASC)
    {
        this->sort(0, SIZE, order);
    }

private:
    ///=============================================================================
    ///=============================================================================
    void sort(T leftIter,
              T rightIter,
              const SortOrder order)
    {
        if (leftIter < rightIter)
        {
            T pivot = partition(leftIter, rightIter, order);
            sort(leftIter, pivot, order);
            sort(leftIter + 1, rightIter, order); // leftIter + 1
        }
    }

    ///=============================================================================
    ///=============================================================================
    T partition(T leftBound,
                T rightBound,
                const SortOrder order)
    {
        T pivot = leftBound;
        T leftIter = leftBound;
        for (int rightIter = leftBound + 1; rightIter < rightBound; ++rightIter)
        {
            if (this->compare(this->m_array[rightIter],
                              this->m_array[pivot], order))
            {
                leftIter += 1;
                this->swap(this->m_array[leftIter],
                           this->m_array[rightIter]);
            }
        }
        this->swap(this->m_array[leftIter],
                   this->m_array[leftBound]);
        return leftIter;
    }
};

#endif // QUICKSORT_H
