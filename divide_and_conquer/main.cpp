#include <iostream>
#include <random>
#include <vector>
#include "tree.h"
#include <algorithm>
#include <queue>
#include <utility>
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
        return binary_search(pole, val, mid-1, l);
    }
}


int binary_search_iterative(const vector<double>& pole, double val)
{
    int l = 0;
    int r = pole.size()-1;

    int mid = (l+r)/2;

    while (pole[mid] != val && !(l > r))
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


void build_perfect_tree(tree& t, const vector<int>& arr, int l, int r)
{
    if (l > r)
    {
        return;
    }

    int mid = (l + r) / 2;
    t.insert(arr[mid]);

    build_perfect_tree(t, arr, l, mid - 1);
    build_perfect_tree(t, arr, mid + 1, r);
}


void build_perfect_tree_iteratively(tree& t, const vector<int>& arr)
{
    int mid;

    queue<pair<int, int>> q;
    q.push({ 0, arr.size()-1});

    while (!q.empty())
    {
        auto [l, r] = q.front();
        q.pop();
        if (l > r)
        {
            continue;
        }
        mid = (l + r) / 2;
        t.insert(mid);
        q.push({ l, mid - 1 });
        q.push({ mid + 1, r });
    }
}


int main()
{
    const int N = 1000;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> dist(0.0, 1000.0);

    vector<double> pole(N, 0.0);

    for (unsigned int i = 0; i < N; i++)
    {
        pole[i] = dist(rng);
    }

    sort(pole.begin(), pole.end());


    std::random_device dev1;
    std::mt19937 rng1(dev1());
    std::uniform_int_distribution<int> dist1(0, 1000);

    vector<int> arr(12, 0);

    for (unsigned int i = 0; i < 12; i++)
    {
        arr[i] = dist1(rng1);
    }

    sort(arr.begin(), arr.end());

    tree t;
    //build_perfect_tree(t, arr, 0, 11);

    build_perfect_tree_iteratively(t, arr);
   
    t.TREEPRINT();


    hanoi h(3);
    h.solve();

}