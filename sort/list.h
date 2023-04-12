#ifndef _LIST_H
#define _LIST_H


#include <initializer_list>

using T = int;


class list
{
	class node;

	node* head;
	node* tail;

	void push_behind(node* node_, const T& data);
	void remove(node* node_);

public:
	list();
	list(const list& src);
	list(std::initializer_list<T> init_list);
	~list() { clear(); }

	bool empty() { return head == nullptr; }
	void clear();

	void pop_front();
	void push_front(const T& data);

	void pop_back();
	void push_back(const T& data);

	void print() const;


	void bubble_sort();
	void better_bubble_sort();
	void selection_sort();
	void shaker_sort();
	void insertion_sort();
};


class list::node
{
	T data;
	node* next;
	node* prev;

public:
	node(const T& data, node* next, node* prev);
	node(const T& data);
	T getData() const { return this->data; }
	void setData(const T& data) { this->data = data; }

	friend class list;
};


#endif //_LIST_H