#pragma once


int smallest_key(int* arr, int right, int from);
void selection_sort(int* arr, int left, int right);

void divide(int* data, int left, int right, int pivot);
void quick_sort_alg(int* data, int left, int right);
void quick_sort_alg_non_rec(int* data, int n);
void quick_sort(int* data, int n);

void shell_sort(int* data, int n);

void radix_sort(int* data, int n);

void bucket_sort(int* data, int n, int K)