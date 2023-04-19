#include <utility>
#include <stack>
#include <cmath>

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


void quick_sort_alg(int* data, int left, int right)
{
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
	//quick_sort_alg(data, 0, n - 1);
	quick_sort_alg_non_rec(data, n);
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
