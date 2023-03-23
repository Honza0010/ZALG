#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <queue>
#include <utility>

#include <stack>

#include "binary_tree.h"
#include "hanoi.h"


using namespace std;



int binary_search(const vector<double>& pole, double val, int l, int r)
{
	if (l > r)
	{
		return -1;
	}

	int mid = (l + r) / 2;

	if (pole[mid] == val)
	{
		return mid;
	}
	else if (val > pole[mid])
	{
		return binary_search(pole, val, mid + 1, r);
	}
	else
	{
		return binary_search(pole, val, l, mid-1);
	}
}

int binary_search_iterative(const vector<double>& pole, double val)
{
	int l = 0;
	int r = pole.size() - 1;

	int mid;

	while (!(l > r))
	{
		mid = (l + r) / 2;
		if (pole[mid] == val)
		{
			return mid;
		}
		else if (pole[mid] < val)
		{
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}
	return -1;
}
	

void build_perfect_tree(binary_tree& t, const vector<int>& pole, int l, int r)
{
	if (l > r)
	{
		return;
	}

	int mid = (l + r) / 2;
	t.insert(pole[mid]);

	build_perfect_tree(t, pole, l, mid - 1);
	build_perfect_tree(t, pole, mid + 1, r);
}


void build_perfect_tree_iteratively(binary_tree& t, const vector<int>& pole)
{
	int mid;

	queue<pair<int, int>> q;

	//stack<pair<int, int>> q;
	q.push({ 0, pole.size() - 1 });

	while (!q.empty())
	{
		auto [l, r] = q.front();
		//auto [l, r] = q.top();
		q.pop();
		if (l > r)
		{
			continue;
		}

		mid = (l + r) / 2;
		t.insert(pole[mid]);
		q.push({ l, mid - 1 });
		q.push({ mid + 1, r });

	}
}

int main()
{
	//vector<double> pole = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0 };

	//int index = binary_search(pole, 5.0, 0, 9);

	//int index2 = binary_search_iterative(pole, 3.0);
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 1000);

	binary_tree t;

	vector<int> arr(10, 0);

	for (int i = 0; i < 10; i++)
	{
		arr[i] = distribution(generator);
	}

	sort(arr.begin(), arr.end());
	//build_perfect_tree(t, arr, 0, 9);
	build_perfect_tree_iteratively(t, arr);
	t.treeprint();

	hanoi h(10);
	h.solve();
}