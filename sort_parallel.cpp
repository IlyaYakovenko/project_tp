#include "sort.h"
#include <iostream>
#include <omp.h>

void merge(void** array, int const left, int const mid,
           int const right, templates::CompareSortType pCompareFunc)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    auto *leftArray = new void*[subArrayOne],
            *rightArray = new void*[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (pCompareFunc(leftArray[indexOfSubArrayOne], rightArray[indexOfSubArrayTwo]) < 0) {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        else {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}


void mergeSortRecursive(void** array, int const begin, int const end, templates::CompareSortType pCompareFunc, int maxDepth) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    if (maxDepth > 0) {
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortRecursive(array, begin, mid, pCompareFunc, maxDepth - 1);

            #pragma omp section
            mergeSortRecursive(array, mid + 1, end, pCompareFunc, maxDepth - 1);
        }

    } else {
        mergeSortRecursive(array, begin, mid, pCompareFunc, 0);
        mergeSortRecursive(array, mid + 1, end, pCompareFunc, 0);
    }
    merge(array, begin, mid, end, pCompareFunc);
}

void templates::mergeSort(void** ppArray, int length, templates::CompareSortType pCompareFunc) {
    omp_set_nested(1);
    int maxDepth = omp_get_max_threads();
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortRecursive(ppArray, 0, length - 1, pCompareFunc, maxDepth);
    }
}


int partition(void** arr, int start, int end, templates::CompareSortType pCompareFunc) {
    auto pivot = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (pCompareFunc(arr[j], pivot) >= 0) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[end]);
    return i + 1;
}

void quickSortRecursive(void** arr, int start, int end, templates::CompareSortType pCompareFunc, int maxDepth)
{
    if (start >= end)
        return;

    int p = partition(arr, start, end, pCompareFunc);

    if (maxDepth > 0) {
#pragma omp parallel sections
        {
#pragma omp section
            quickSortRecursive(arr, start, p - 1, pCompareFunc, maxDepth - 1);

#pragma omp section
            quickSortRecursive(arr, p + 1, end, pCompareFunc, maxDepth - 1);
        }
    } else {
        quickSortRecursive(arr, start, p - 1, pCompareFunc, 0);
        quickSortRecursive(arr, p + 1, end, pCompareFunc, 0);
    }
}

void templates::quickSort(void** ppArray, int length, templates::CompareSortType pCompareFunc){
    omp_set_nested(1);
    int maxDepth = omp_get_max_threads();
    #pragma omp parallel
    {
        #pragma omp single
        quickSortRecursive(ppArray, 0, length - 1, pCompareFunc, maxDepth);
    }

}
