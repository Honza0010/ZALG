#include <iostream>
#include <vector>
#include <random>

using namespace std;


const int N = 15;



void insert_from_to(int* arr, int data, int from, int to)
{
    for (int i = from; i > to; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[to] = data;
}

//
void insertion_sort(int* arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        int pos = i;

        for (; pos > 0 && arr[pos - 1] > arr[i]; pos--)//while(pos > 0 && arr[pos - 1] > arr[i])//
        {
            //pos--;
        }
        if (pos != i)
        {
            //int help = arr[i];

            //for (int j = i; j > pos; j--)
            //{
            //    arr[j] = arr[j - 1];
            //}
            //arr[pos] = help;
            insert_from_to(arr, arr[i], i, pos);
        }
    }
}
//


//Start of binary insertion sort
int binary_search(int* arr, int current_index, int data)
{
    int l = 0;
    int r = current_index;

    while (l < r)
    {
        int mid = (l + r) / 2;

        if (arr[mid] >= data)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}


void binary_insertion_sort(int* arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        int pos = binary_search(arr, i, arr[i]);
        if (pos != i)
        {
            insert_from_to(arr, arr[i], i, pos);
        }
    }
}
//


//Start of selection sort
int smallest_key(int* arr, int n, int from)
{
    for (int i = from; i < n; i++)
    {
        if (arr[i] < arr[from])
        {
            from = i;
        }
    }
    return from;
}

void selection_sort(int* arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int smallest_index = smallest_key(arr, n, i);       //We find the index of the smallest element in the subarray starting by index i
        if (smallest_index != i)
        {
            int help = arr[i];
            arr[i] = arr[smallest_index];
            arr[smallest_index] = help;
        }
    }
}
//


void bubble_sort(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int help = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = help;
            }
        }
    }
}

void better_bubble_sort(int* arr, int n)
{
    bool changes = true;
    int last_change = n - 1;

    while (changes)     //Until there are changes we continue sorting
    {
        changes = false;

        int last_change_sentinel = last_change;
        for (int i = 0; i < last_change_sentinel; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int help = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = help;
                last_change = i;
                changes = true;
            }
        }
    }
}



void shaker_sort(int* arr, int n)
{
    bool changes = true;
    int last_change = n - 1;
    int l = 0;
    int r = n - 1;
    do
    {
        changes = false;
        for (int i = l; i < r; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int help = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = help;
                changes = true;
                last_change = i;
            }
        }
        r = last_change;

        for (int i = r; i > l; i--)
        {
            if (arr[i] < arr[i - 1])
            {
                int help = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = help;
                changes = true;
                last_change = i;
            }
        }
        l = last_change;
    } while (l < r && changes);
}


void print_array(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}


int main()
{
    int array_[N];

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100); // distribution in range [1, 6]

    for (int i = 0; i < N; i++)
    {
        array_[i] = dist(rng);
    }

    print_array(array_, N);

    //insertion_sort(array_, N);
    //binary_insertion_sort(array_, N);
    //selection_sort(array_, N);
    //bubble_sort(array_, N);
    //better_bubble_sort(array_, N);
    shaker_sort(array_, N);
    print_array(array_, N);
}