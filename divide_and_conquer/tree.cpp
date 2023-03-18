#include "tree.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <cmath>

tree::node::node(T data)
	: data(data)
{
	depth = 0;
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
	number_of_nodes = 0;
	depth = 0;
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

	number_of_nodes = 0;
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
		number_of_nodes++;
		return;
	}
	node* help = root;

	int help_depth = 0;

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
				help->right->setDepth(help_depth + 1);
				number_of_nodes++;

				this->depth = (help_depth+1) > this->depth ? (help_depth+1) : depth;

				return;
			}
			help = help->right;
			help_depth++;
		}
		else
		{
			if (help->left == nullptr)
			{
				help->left = new node(data);
				help->left->setDepth(help_depth + 1);
				number_of_nodes++;

				this->depth = (help_depth + 1) > this->depth ? (help_depth + 1) : this->depth;

				return;
			}
			help = help->left;
			help_depth++;
		}
	}
}

void tree::insert_recursively(const T& data)
{
	if (empty())
	{
		root = new node(data);
		number_of_nodes++;
		return;
	}
	insert_into_subtree(data, root, 0);
}


void tree::insert_into_subtree(const T& data, node* node_, int depth_)
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
			node_->right->setDepth(depth_ + 1);

			this->depth = (depth_ + 1) > this->depth ? (depth_ + 1) : this->depth;

			number_of_nodes++;
		}
		else
		{
			insert_into_subtree(data, node_->right, depth_+1);
		}
	}
	else
	{
		if (node_->left == nullptr)
		{
			node_->left = new node(data);
			node_->left->setDepth(depth_ + 1);

			this->depth = (depth_ + 1) > this->depth ? (depth_ + 1) : this->depth;

			number_of_nodes++;
		}
		else
		{
			insert_into_subtree(data, node_->left, depth_ + 1);
		}
	}

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
	number_of_nodes--;

	this->depth = getDepth(root)-1;
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
	number_of_nodes--;

	this->depth = getDepth(root)-1;
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


int tree::getDepth(node* node_)
{
	if (node_ != nullptr)
	{
		int l = 0, p = 0;
		l = getDepth(node_->left);
		p = getDepth(node_->right);
		return l > p ? (l + 1) : (p + 1);
	}
	return 0;

}


void tree::TREEPRINT()
{
	int i = 0;
	while (i <= this->depth) {
		printlv(i);
		i++;
		std::cout << std::endl;
	}
}



void tree::printlv(int n)
{
	node* temp = root;


	int val = pow(2, this->depth - n + 2);
	std::cout << std::setw(val) << "";
	dispLV(temp, n, val);
	
}

void tree::dispLV(node* p, int lv, int d)
{
	int disp = 2*d;
	if (lv == 0) {
		if (p == nullptr) {

			std::cout << "x";
			std::cout << std::setw(disp-1) << "";
			return;
		}
		else {
			int result = ((p->data <= 1) ? 1 : log10(p->data) + 1);
			std::cout << p->data;
			//std::cout << std::setw(disp - result - 2) << "";
			std::cout << std::setw(disp - result) << "";
		}
	}
	else
	{
		if (p == nullptr && lv >= 1) {
			dispLV(nullptr, lv - 1, d);
			dispLV(nullptr, lv - 1, d);
		}
		else {
			dispLV(p->left, lv - 1, d);
			dispLV(p->right, lv - 1, d);
		}
	}
}


void tree::treeprint2()
{
	struct node_help
	{
		node* p;
		bool is_separator;		//Bude kontrolovat, zda vložený nullptr je "chybìjící" prvek a nebo separátor oddìlující úrovnì
	};

	std::queue<node_help> q;

	q.push(node_help{root, false});
	q.push(node_help{nullptr, true});
	int help_depth = 0;

	int val = pow(2, this->depth - root->depth + 2);		//Odsazení od kraje
	std::cout << std::setw(val) << "";
	while (!q.empty())
	{
		node_help help = q.front();
		q.pop();
		if (help.p != nullptr)
		{
			q.push(node_help{ help.p->left, false });
			q.push(node_help{ help.p->right, false });

			int result = ((help.p->data <= 1) ? 1 : log10(help.p->data) + 1);		//Kontroluje, kolika ciferné je èíslo
			std::cout << help.p->data;
			val = pow(2, this->depth - help.p->depth + 2);
			std::cout << std::setw(2*val - result) << "";

		}
		else if(help.is_separator == true)
		{
			help_depth++;		//Pøi pøechodu na novou úroveò zvìtšíme pomocný level
			if (q.empty())
			{
				break;
			}
			std::cout << std::endl;

			val = pow(2, this->depth - help_depth + 2);			//Odsazení od kraje
			std::cout << std::setw(val) << "";
			q.push(node_help{ nullptr, true });
			if (help_depth > this->depth)		//Jestliže jsme už pøekroèili nejnižší patro, tak konèíme
			{
				break;
			}
		}
		else
		{
			q.push(node_help{ nullptr, false });
			q.push(node_help{ nullptr, false });
			std::cout << "x";
			val = pow(2, this->depth - help_depth + 2);
			std::cout << std::setw(2*val - 1) << "";		// -1 protože x je jednomistne
		}
	}
}


void tree::write()
{
	if (empty())
	{
		return;
	}
	write_(root, 0);
}


void tree::write_(node* node_, int n)
{
	if (node_ == nullptr)
	{
		return;
	}
	write_(node_->left, n + 1);

	for (int i = 0; i < n; i++)
	{
		std::cout << " ";
	}
	std::cout << node_->data << std::endl;
	write_(node_->right, n + 1);
}


void tree::wide_print()
{
	unsigned int h = getDepth(root);
	unsigned int space = (1 << (h - 1));		//equivalnt to space = std::pow(2, n); 
	std::queue<node*> q;
	q.push(root);
	node* curr;

	for (unsigned int i = 1; i <= h; i++)
	{
		unsigned int level_size = q.size();
		for (unsigned int j = 0; j < level_size; j++)
		{
			curr = q.front();
			q.pop();
			std::cout << std::setw(space * 2) << std::right;
			if (curr) {
				q.push(curr->left);
				q.push(curr->right);
				std::cout << curr->data;
			}
			else {
				q.push(nullptr);
				q.push(nullptr);
				std::cout << "  ";
			}
			std::cout << std::setw(space * 2) << " ";
		}
		space /= 2;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}