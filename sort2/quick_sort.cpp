#include <utility>
#include <stack>
#include <vector>

void divide(int* data, int left, int right, int pivot)
{
	while (left <= right)
	{
		while (data[left] < pivot)
		{
			left++;
		}
		while (pivot < data[right])
		{
			right--;
		}
		if (left <= right)
		{
			std::swap(data[left], data[right]);
			left++;
			right--;
		}
	}
}


//Start of selection sort
int smallest_key(int* arr, int right, int from)
{
	for (int i = from; i < right + 1; i++)
	{
		if (arr[i] < arr[from])
		{
			from = i;
		}
	}
	return from;
}

void selection_sort(int* arr, int left, int right)
{
	for (int i = left; i < right; i++)
	{
		int smallest_index = smallest_key(arr, right, i);       //We find the index of the smallest element in the subarray starting by index i
		if (smallest_index != i)
		{
			int help = arr[i];
			arr[i] = arr[smallest_index];
			arr[smallest_index] = help;
		}
	}
}
//


void quick_sort_alg(int* data, int left, int right)
{
	if (right - left + 1 < 3)
	{
		selection_sort(data, left, right);
		return;
	}


	int i = left;
	int j = right;
	int pivot = data[(left + right) / 2];

	while (i <= j)
	{
		while (data[i] < pivot)
		{
			i++;
		}
		while (pivot < data[j])
		{
			j--;
		}
		if (i <= j)
		{
			std::swap(data[i], data[j]);
			i++;
			j--;
		}
	}
	if (left < j)
	{
		quick_sort_alg(data, left, j);
	}
	if (i < right)
	{
		quick_sort_alg(data, i, right);
	}
}



void quick_sort_alg_non_rec(int* data, int n)
{
	std::stack<std::pair<int, int>> s;
	//int left, right;
	s.emplace(0, n - 1);

	while (!s.empty())
	{
		auto [left, right] = s.top();
		s.pop();
		int pivot = data[(left + right) / 2];
		int i = left, j = right;

		while (i <= j)
		{
			while (data[i] < pivot)
			{
				i++;
			}
			while (pivot < data[j])
			{
				j--;
			}
			if (i <= j)
			{
				std::swap(data[i], data[j]);
				i++;
				j--;
			}
		}
		if (left < j)
		{
			s.emplace(left, j);
		}
		if (i < right)
		{
			s.emplace(i, right);
		}
	}
}


void quick_sort(int* data, int n)
{
	quick_sort_alg(data, 0, n - 1);
}




void shell_sort(int* data, int n)
{
	// Start with a big gap, then reduce the gap until it becomes 1
	for (int gap = pow(2, (int)log2(200)) - 1; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size.
		// The first gap elements a[0..gap-1] are already in gapped order
		// keep adding one more element until the entire array is gap sorted
		for (int i = gap; i < n; i++)
		{
			// add a[i] to the elements that have been gap sorted
			// save a[i] in temp and make a hole at position i
			int temp = data[i];

			// shift earlier gap-sorted elements up until the correct location for a[i] is found
			int j;
			for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
			{
				data[j] = data[j - gap];
			}

			// put temp (the original a[i]) in its correct location
			data[j] = temp;
		}
	}
}


void radix_sort(int* data, int n)
{
	std::vector<std::vector<int>> fronty(10, std::vector<int>());

	int z = 10;
	int d = 1;

	int x;
	int j;
	for (int i = 0; i < 4; i++)
	{
		for (int i = 0; i < n; i++)
		{
			x = data[i];
			j = (x / d) % z;
			fronty[j].push_back(x);
		}
		d = d * z;


		int help = 0;
		for (int k = 0; k < 10; k++)
		{
			for (int index = 0; index < fronty[k].size(); index++)
			{
				data[help] = fronty[k][index];
				help++;
			}
			fronty[k].clear();
		}

	}
}