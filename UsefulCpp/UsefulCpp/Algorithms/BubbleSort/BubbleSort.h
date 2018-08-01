#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "..\SortingCore.h"

///=============================================================================
/// Simple implementation of "Bubble Sort".
///
/// Example of usage:
/// constexpr size_t arrSize = 20;
/// int inputArray[arrSize]{ 9, 85, 7, 6, 53, 4, 3, 21, 1, ... };
/// BubbleSort<int, arrSize> bubbleSort(inputArray);
/// bubbleSort.sort();
/// bubbleSort.print();
///=============================================================================
template <typename T, size_t SIZE>
class BubbleSort : public SortingCore<T, SIZE>
{
public:
    ///=============================================================================
    ///=============================================================================
    BubbleSort(T* inputArray)
        : SortingCore<T, SIZE>(inputArray)
    {}

    ///=============================================================================
    ///=============================================================================
    ~BubbleSort() {}

    ///=============================================================================
    ///=============================================================================
    void sort(const SortOrder order = SortOrder::ASC)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 1; j < (SIZE - i); ++j)
            {
                if (this->compare(this->m_array[j - 1],
                                  this->m_array[j], order))
                {
                    this->swap(this->m_array[j - 1], this->m_array[j]);
                }
            }
        }
    }
};

#endif // BUBBLESORT_H

