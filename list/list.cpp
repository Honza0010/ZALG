#include "list.h"
#include <iostream>

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

void list::print() const
{
	for (node* help = head; help != nullptr; help = help->next)
	{
		std::cout << help->data << ", ";
	}
	std::cout << "\n";
}
