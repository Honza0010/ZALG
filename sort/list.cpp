#include "list.h"
#include <iostream>
#include <utility>

list::node::node(const T& data, node* next, node* prev)
	: data(data), next(next), prev(prev)
{
}

list::node::node(const T& data)
	: data(data), next(nullptr), prev(nullptr)
{
}


list::list()
{
	head = tail = nullptr;
}

list::list(const list& src)
{
	for (node* help = src.head; help != nullptr; help = help->next)
	{
		push_back(help->getData());
	}
}

list::list(std::initializer_list<T> init_list)
{
	for (auto i : init_list)
	{
		push_back(i);
	}
}

void list::clear()
{
	while (!empty())
	{
		pop_front();
	}
}

void list::pop_front()
{
	if (empty())
	{
		return;
	}

	node* help = head;

	if (head == tail)
	{
		head = tail = nullptr;
	}
	else
	{
		head = head->next;
		head->prev = nullptr;
	}

	delete help;
}

void list::push_front(const T& data)
{
	node* help = new node(data, head, nullptr);

	if (!empty())
	{
		head->prev = help;
	}

	head = help;

	if (tail == nullptr)
	{
		tail = head;
	}
}

void list::pop_back()
{
	if (empty())
	{
		return;
	}

	node* help = tail;

	if (head == tail)
	{
		head = tail = nullptr;
	}
	else
	{
		tail = tail->prev;
		tail->next = nullptr;
	}
	delete help;
}

void list::push_back(const T& data)
{
	node* help = new node(data, nullptr, tail);

	if (!empty())
	{
		tail->next = help;
	}

	tail = help;

	if (head == nullptr)
	{
		head = tail;
	}
}

void list::push_behind(node* node_, const T& data)
{
	if (node_ == tail)
	{
		push_back(data);
		return;
	}

	node* new_node = new node{ data, node_->next, node_ };
	node_->next = new_node;
	new_node->next->prev = new_node;
}

void list::remove(node* node_)
{
	{
		if (node_ == nullptr) 
		{
			return;
		}
		if (node_ == head)
		{
			pop_front();
		}
		else if (node_ == tail)
		{
			pop_back();
		}
		else 
		{
			node_->prev->next = node_->next;
			node_->next->prev = node_->prev;
			delete node_;
		}
	}
}


void list::print() const
{
	for (node* help = head; help != nullptr; help = help->next)
	{
		std::cout << help->data << ", ";
	}
	std::cout << "\n";
}

void list::bubble_sort()
{
	for (node* pom = head; pom != nullptr; pom = pom->next)
	{
	/*	for (node* help = head; help->next != nullptr; help = help->next)
		{
			if (help->data > help->next->data)
			{
				std::swap(help->data, help->next->data);
			}
		}*/
		node* help_tail = tail;
		for (node* help = head; help->next != help_tail->next; help = help->next)
		{
			if (help->data > help->next->data)
			{
				std::swap(help->data, help->next->data);
			}
		}
		help_tail = help_tail->prev;
	}
}

void list::better_bubble_sort()
{
	bool changes = true;
	node* last_change = nullptr;

	while (changes)
	{
		changes = false;

		node* last_change_sentinel = last_change;

		for (node* help = head; help->next != last_change_sentinel; help = help->next)
		{
			if (help->data > help->next->data)
			{
				std::swap(help->data, help->next->data);
				last_change = help->next;
				changes = true;
			}
		}
	}
}

void list::selection_sort()
{
	for (node* help = head; help->next != nullptr; help = help->next)
	{
		T min = help->getData();
		node* min_node = nullptr;
		for (node* help_1 = help->next; help_1 != nullptr; help_1 = help_1->next)
		{
			if (help_1->getData() < min)
			{
				min = help_1->getData();
				min_node = help_1;
			}
		}
		if (min_node != nullptr)
		{
			min_node->setData(help->getData());
			help->setData(min);
		}
	}
}

void list::shaker_sort()
{
	node* left = head;
	node* right = tail;
	node* last_change = tail;

	while (left != right)
	{
		last_change = right;
		for (node* help = left; help != right; help = help->next)
		{
			if (help->data > help->next->data)
			{
				std::swap(help->data, help->next->data);
				last_change = help;
			}
		}

		if (last_change == right)
		{
			return;
		}
		right = last_change;


		last_change = left;
		for (node* help = right; help != left; help = help->prev)
		{
			if (help->prev->data > help->data)
			{
				std::swap(help->prev->data, help->data);
				last_change = help;
			}
		}
		if (left == last_change)
		{
			return;
		}

		left = last_change;

	}
}

void list::insertion_sort()
{
	if (empty())
	{
		return;
	}

	for (node* help = head->next; help != nullptr; help = help->next) {
		node* first_bigger = head;

		if (help->data > help->prev->data) {
			continue;
		}

		while (first_bigger->data < help->data) {
			first_bigger = first_bigger->next;
		}

		if (first_bigger == head) {
			push_front(help->data);
		}
		else {
			push_behind(first_bigger->prev, help->data);
		}
		help = help->prev;
		remove(help->next);
	}
}
