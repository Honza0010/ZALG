#include <iostream>
#include <utility>
#include "quick_sort.h"

using namespace std;


const int N = 10;

void insert_into_heap(int* data, int left, int right)
{
	int i = left;
	int j = 2 * i + 1;
	int x = data[i];

	while (j <= right)
	{
		if (j < right)
		{
			if (data[j] < data[j + 1])		//We choose bigger child to compare with inserted x
			{
				j++;
			}
		}
		if (x >= data[j])	//If x is bigger than both its children then we can end
		{
			break;
		}
		data[i] = data[j];		//If x is not bigger than its children we switch x with its bigger child
		i = j;					//We move forward to the position of the switched child
		j = 2 * i + 1;			//We have to again check whether the x is bigger than its other children
	}
	data[i] = x;
}


void heap_sort(int* data, int n)
{
	int left = n / 2;
	int right = n - 1;

	while (left)		//We will create heap
	{
		left--;
		insert_into_heap(data, left, right);
	}		//Now we created heap and the biggest element is in the root

	while (right)
	{
		swap(data[left], data[right]);		//We give the biggest element into the end of the array and again create heap in the same array from root to index n-2
		right--;							//We have to decrease its right border;
		insert_into_heap(data, 0, right);	//Again we create heap, because the sequence data[1] ... data[n-2] is a heap
	}
}


void print(int* data, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

int main()
{
	int data[N];

	for (int i = 0; i < N; i++)
	{
		data[N - i - 1] = i;
	}
	print(data, N);
	//heap_sort(data, N);
	//quick_sort(data, N);
	shell_sort(data, N);

	print(data, N);
}