#include "tree.h"
#include <iostream>

tree::node::node(T data)
	: data(data)
{
	left = nullptr;
	right = nullptr;
}

T tree::node::getData() const
{
	return this->data;
}

void tree::node::setData(const T& data)
{
	this->data = data;
}

tree::tree()
{
	root = nullptr;
}

tree::~tree()
{
	clear();
}

void tree::clear()
{
	if (empty())
	{
		return;
	}
	remove_all(root);
}

void tree::remove_all(node* node_)
{
	if (node_ == nullptr)
	{
		return;
	}
	remove_all(node_->left);
	remove_all(node_->right);
	delete node_;
}

bool tree::empty() const
{
	return root == nullptr;
}

void tree::insert(const T& data)
{
	if (empty())
	{
		root = new node(data);
		return;
	}
	node* help = root;

	while (true)
	{
		if (data == help->getData())
		{
			return;
		}
		if (data > help->getData())
		{
			if (help->right == nullptr)
			{
				help->right = new node(data);
				return;
			}
			help = help->right;
		}
		else
		{
			if (help->left == nullptr)
			{
				help->left = new node(data);
				return;
			}
			help = help->left;
		}
	}
}

void tree::insert_recursively(const T& data)
{
	if (empty())
	{
		root = new node(data);
		return;
	}
	insert_into_subtree(data, root);
}

tree::node* tree::find_recursively(const T& data, node* &parent)
{
	parent = nullptr;
	return find_in_subtree(data, parent, root);
}

tree::node* tree::find_iteratively(const T& data, node*& parent)
{
	parent = nullptr;
	if (empty())
	{
		return nullptr;
	}
	node* help = root;

	while (help != nullptr)
	{
		if (help->getData() == data)
		{
			return help;
		}
		parent = help;
		if (data > help->getData())
		{
			if (help->right == nullptr)
			{
				return nullptr;
			}
			help = help->right;
		}
		else
		{
			if (help->left == nullptr)
			{
				return nullptr;
			}
			help = help->left;
		}
	}
}


tree::node* tree::find_in_subtree(const T& data, node* &parent, node* node_)
{
	if (node_ == nullptr)
	{
		return nullptr;
	}
	if (node_->getData() == data)
	{
		return node_;
	}
	parent = node_;
	if (node_->getData() < data)
	{
		return find_in_subtree(data, parent, node_->right);
	}
	else
	{
		return find_in_subtree(data, parent, node_->left);
	}
}

void tree::insert_into_subtree(const T& data, node* node_)
{
	if (node_->getData() == data)
	{
		return;
	}

	if (data > node_->getData())
	{
		if (node_->right == nullptr)
		{
			node_->right = new node(data);
		}
		else
		{
			insert_into_subtree(data, node_->right);
		}
	}
	else
	{
		if (node_->left == nullptr)
		{
			node_->left = new node(data);
		}
		else
		{
			insert_into_subtree(data, node_->left);
		}
	}

}





void tree::write() const
{
	if (empty())
	{
		return;
	}
	write_(root, 0);
}

void tree::write_find(const T& data)
{
	node* parent = nullptr;
	node* help = find_recursively(data, parent);

	std::cout << parent->getData() << " " << help->getData() << std::endl;
}

void tree::remove_node(const T& data)
{
	node* parent = nullptr;
	node* deleted = find_recursively(data, parent);

	if (deleted == nullptr)
	{
		return;
	}

	if (!deleted->left && !deleted->right)
	{
		remove_leaf(deleted, parent);
	}
	else if (deleted->left && deleted->right)
	{
		remove_two_children(deleted, parent);
	}
	else
	{
		remove_one_child(deleted, parent);
	}
}

void tree::remove_leaf(node* deleted, node* parent)
{
	if (parent)
	{
		if (parent->left == deleted)
		{
			parent->left = nullptr;
		}
		else
		{
			parent->right = nullptr;
		}
	}
	else
	{
		root = nullptr;
	}
	delete deleted;
}

void tree::remove_one_child(node* deleted, node* parent)
{
	if (parent)
	{
		if (parent->left == deleted)
		{
			parent->left = deleted->left ? deleted->left : deleted->right;
		}
		else
		{
			parent->right = deleted->left ? deleted->left : deleted->right;
		}
	}
	else
	{
		root = deleted->left ? deleted->left : deleted->right;
	}
	delete deleted;
}

void tree::remove_two_children(node* deleted, node* parent)
{
	node* help = deleted->left;
	parent = deleted;

	while (help->right)
	{
		parent = help;
		help = help->right;
	}

	deleted->setData(help->getData());

	help->left ? remove_one_child(help, parent) : remove_leaf(help, parent);
}

void tree::write_(node* node_, int n) const
{
	if (node_ == nullptr)
	{
		return;
	}
	write_(node_->left, n+1);

	for (int i = 0; i < n; i++)
	{
		std::cout << " ";
	}
	std::cout << node_->data << std::endl;
	write_(node_->right, n+1);
}








