#include <tuple>
#include <stack>

#include "merge_sort.h"

using namespace std;

void merge(int* arr, int l1, int r1, int l2, int r2) 
{
    int i, j, k;
    int n1 = r1 - l1 + 1;       //Size of the left array
    int n2 = r2 - l2 + 1;       //Size of the right array

    int* pom = new int[n1 + n2];        //Array of the size n1+n2 because we merge (join) them

    i = l1;
    j = l2;
    k = 0;

    while (i <= r1 && j <= r2)  //Iterate until we have values in both arrays to compare
    {
        if (arr[i] <= arr[j])   //If the value in left array is smaller we write it into pom array and go to the next value in this array
        {
            pom[k] = arr[i];
            i++;
        }
        else 
        {
            pom[k] = arr[j];
            j++;
        }
        k++;    //We have to step onto next position in pom array
    }

    while (i <= r1)     //We have to copy the rest of the left array (if there are some elements left) into pom array
    {
        pom[k] = arr[i];
        i++;
        k++;
    }

    
    //Rest of the right array is not necessary to copy into pom because it has already been in the right position

    for (i = l1, j = 0; j < k; j++, i++)    //It copies pom array back into arr in the correct order
        arr[i] = pom[j];

    delete[] pom;
}

void merge_sort_rec(int* arr, int left, int right) 
{
    if (left == right)
        return;

    int middle = left + (right - left) / 2;

    merge_sort_rec(arr, left, middle);  //We divide it into left array (exactly in the middle)
    merge_sort_rec(arr, middle + 1, right); //Into right subarray

    merge(arr, left, middle, middle + 1, right);    //Finally we merge it
}

void merge_sort(int* arr, int n) 
{
    enum signature 
    {
        SPLIT, MERGE
    };
    std::stack<std::tuple<signature, int, int, int>> stack1;

    if (n < 2)
        return;

    stack1.emplace(SPLIT, 0, (n - 1) / 2, n - 1);

    while (!stack1.empty()) 
    {
        auto [sign, left, middle, right] = stack1.top();
        stack1.pop();
        if (sign == SPLIT) 
        {
            stack1.emplace(MERGE, left, middle, right);
            if (left < middle)
                stack1.emplace(SPLIT, left, (left + middle) / 2, middle);
            if (middle + 1 < right)
                stack1.emplace(SPLIT, middle + 1, (middle + 1 + right) / 2, right);
        }
        else 
        {
            merge(arr, left, middle, middle + 1, right);
        }
    }
}