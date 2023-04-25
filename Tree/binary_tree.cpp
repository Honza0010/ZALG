#include "binary_tree.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <iomanip>
#include <queue>

binary_tree::node::node(const T& data)
	: data(data), left(nullptr), right(nullptr), depth(0)
{

}

int binary_tree::node::getData() const
{
	return this->data;
}

binary_tree::binary_tree()
{
	root = nullptr;
	number_of_elements = 0;
	number_of_levels = 0;
}

binary_tree::~binary_tree()
{
	remove_all(root);
	number_of_elements = 0;
	number_of_levels = 0;
}

bool binary_tree::empty()
{
	return root == nullptr;
}

void binary_tree::remove_all(node* node_)
{
	if (node_ == nullptr)
	{
		return;
	}

	remove_all(node_->left);
	remove_all(node_->right);

	delete node_;
}

void binary_tree::insert(const T& data)
{
	if (empty())
	{
		root = new node(data);
		number_of_elements++;
		return;
	}

	insert_into_subtree(data, root, 0);
}

void binary_tree::insert_iteratively(const T& data)
{
	if (empty())
	{
		root = new node(data);
		number_of_elements++;
		return;
	}

	node* help = root;

	int help_depth = 0;

	while (true)
	{
		if (data == help->data)
		{
			return;
		}
		else if (data > help->data)
		{
			if (help->right == nullptr)
			{
				help->right = new node(data);
				help->right->depth = help_depth + 1;
				number_of_elements++;

				this->number_of_levels = (help_depth + 1) > this->number_of_levels ? (help_depth + 1) : this->number_of_levels;
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
				help->left->depth = help_depth + 1;
				number_of_elements++;

				this->number_of_levels = (help_depth + 1) > this->number_of_levels ? (help_depth + 1) : this->number_of_levels;
				return;
			}
			help = help->left;
			help_depth++;
		}
	}
}




void binary_tree::insert_into_subtree(const T& data, node* node_,unsigned int depth_)
{
	if (node_->getData() == data)
	{
		return;
	}
	else if (data > node_->getData())
	{
		if (node_->right == nullptr)
		{
			node_->right = new node(data);
			node_->right->depth = depth_ + 1;
			number_of_elements++;

			this->number_of_levels = (depth_ + 1) > this->number_of_levels ? (depth_ + 1) : this->number_of_levels;
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
			node_->left->depth = depth_ + 1;
			number_of_elements++;

			this->number_of_levels = (depth_ + 1) > this->number_of_levels ? (depth_ + 1) : this->number_of_levels;
		}
		else
		{
			insert_into_subtree(data, node_->left, depth_+1);
		}
	}

}


binary_tree::node* binary_tree::find_iteratively(const T& data, node*& parent)
{
	parent = nullptr;
	if (empty())
	{
		return nullptr;
	}

	node* help = root;

	while (help != nullptr)
	{
		if (data == help->getData())
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

		if (data < help->getData())
		{
			if (help->left == nullptr)
			{
				return nullptr;
			}
			help = help->left;
		}
	}
}


binary_tree::node* binary_tree::find(const T& data, node*& parent)
{
	parent = nullptr;
	return find_in_subtree(data, parent, root);
}



binary_tree::node* binary_tree::find_in_subtree(const T& data, node*& parent, node* node_)
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



void binary_tree::write() const
{
	write_(root);
}



void binary_tree::remove_node(const T& data)
{
	node* parent = nullptr;
	node* to_delete = find_iteratively(data, parent);

	if (to_delete == nullptr)
	{
		return;
	}

	if (to_delete->left && to_delete->right)
	{
		remove_with_two_children(to_delete, parent);
	}
	else if (to_delete->left || to_delete->right)
	{
		remove_with_one_child(to_delete, parent);
	}
	else
	{
		remove_leaf(to_delete, parent);
	}
}




void binary_tree::remove_leaf(node* to_delete, node* parent)
{
	if (parent)
	{
		if (parent->left == to_delete)
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

	delete to_delete;
	number_of_elements--;

	this->number_of_levels = getDepth(root);
}

void binary_tree::remove_with_one_child(node* to_delete, node* parent)
{
	if (parent)
	{
		if (parent->left == to_delete)
		{
			parent->left = to_delete->left ? to_delete->left : to_delete->right;
			/*if (to_delete->left)
			{
				parent->left = to_delete->left;
			}
			else
			{
				parent->left = to_delete->right;
			}*/
		}
		else
		{
			parent->right = to_delete->left ? to_delete->left : to_delete->right;
		}
	}
	else
	{
		root = to_delete->left ? to_delete->left : to_delete->right;
	}

	delete to_delete;
	number_of_elements--;

	this->number_of_levels = getDepth(root);
}

void binary_tree::remove_with_two_children(node* to_delete, node* parent)
{
	node* help = to_delete->left;
	parent = to_delete;

	while (help->right != nullptr)
	{
		parent = help;
		help = help->right;
	}

	to_delete->data = help->getData();

	if (help->left != nullptr)
	{
		remove_with_one_child(help, parent);
	}
	else
	{
		remove_leaf(help, parent);
	}
}



int binary_tree::getDepth(node* node_)
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


void binary_tree::write_(node* node_) const
{
	if (node_ == nullptr)
	{
		return;
	}
	write_(node_->left);
	std::cout << node_->getData() << " ";
	write_(node_->right);

}





void binary_tree::stack_write()
{
	std::stack<node*> s;

	node* help = root;

	while (help != nullptr || !s.empty())
	{

		while (help != nullptr)
		{
			s.push(help);
			help = help->left;
		}

		help = s.top();
		s.pop();

		std::cout << help->data << " ";

		help = help->right;

	}

	std::cout << std::endl;
}



void binary_tree::treeprint()
{
	int i = 0;
	while (i <= this->number_of_levels) {
		print_lvl(i);
		i++;
		std::cout << std::endl;
	}
}



void binary_tree::print_lvl(int n)
{
	node* temp = root;


	int val = pow(2, this->number_of_levels - n + 2);
	std::cout << std::setw(val) << "";
	display_lvl(temp, n, val);
}

void binary_tree::display_lvl(node* help, int lvl, int d)
{
	int disp = 2 * d;
	if (lvl == 0) {
		if (help == nullptr) {

			std::cout << "x";
			std::cout << std::setw(disp - 1) << "";
			return;
		}
		else {
			int result = ((help->data <= 1) ? 1 : log10(help->data) + 1);
			std::cout << help->data;
			//std::cout << std::setw(disp - result - 2) << "";
			std::cout << std::setw(disp - result) << "";
		}
	}
	else
	{
		if (help == nullptr && lvl >= 1) {
			display_lvl(nullptr, lvl - 1, d);
			display_lvl(nullptr, lvl - 1, d);
		}
		else {
			display_lvl(help->left, lvl - 1, d);
			display_lvl(help->right, lvl - 1, d);
		}
	}
}


void binary_tree::treeprint2()
{
	struct node_help
	{
		node* p;
		bool is_separator;
	};

	std::queue<node_help> q;

	q.push(node_help{ root, false });
	q.push(node_help{ nullptr, true });

	int help_depth = 0;

	int space = pow(2, this->number_of_levels - root->depth + 2);
	std::cout << std::setw(space) << "";

	while (!q.empty())
	{
		node_help help = q.front();
		q.pop();

		if (help.p != nullptr)
		{
			q.push(node_help{ help.p->left, false });
			q.push(node_help{ help.p->right, false });

			int result = ((help.p->data <= 1) ? 1 : log10(help.p->data) + 1);

			std::cout << help.p->data;

			space = pow(2, this->number_of_levels - help.p->depth + 2);
			std::cout << std::setw(2 * space - result) << "";
		}
		else if (help.is_separator == true)
		{
			help_depth++;

			if (q.empty())
			{
				break;
			}

			std::cout << std::endl;
			space = pow(2, this->number_of_levels - help_depth + 2);
			std::cout << std::setw(space) << "";
			q.push(node_help{ nullptr, true });

			if (help_depth > this->number_of_levels)
			{
				break;
			}
		}
		else
		{
			q.push(node_help{ nullptr, false });
			q.push(node_help{ nullptr, false });
			std::cout << "x";
			space = pow(2, this->number_of_levels - help_depth + 2);

			std::cout << std::setw(2 * space - 1) << "";
		}
	}
}

void binary_tree::wide_print()
{
	unsigned int h = getDepth(root); // Vypocti vysku stromu
	unsigned int space = (1 << (h - 1)); // mezera pred a za kazdym prvkem je 2^(h-1)
	std::queue<node*> q; // Fronta na uchovavani jednotlivych urovni stromu
	q.push(root);        // vloz 1. uroven do stromu
	node* curr;          // pomocna promenna ukazujici na aktualni vypisovany prvek

	for (unsigned int i = 1; i <= h; i++) // Projdi vsech h pater
	{
		unsigned int level_size = q.size(); // velikost i-te urovne - (slo by i jinak protoze delame siroky vypis, ale lookup na q.size() je O(1) takze neni potreba rucne pocitat)
		for (unsigned int j = 0; j < level_size; j++) // Projdi vsech k prvku na patre
		{
			// postupne vyjmi kazdy prvek z i-teho patra
			curr = q.front();
			q.pop();
			//
			std::cout << std::setw(space * 2) << std::right; // cislo kterym nasobime space je maximalni pocet cislic klice
			if (curr) { // existuje-li aktualni prvek
				// vloz jeho syny do frontu (do dalsiho patra)
				q.push(curr->left);
				q.push(curr->right);
				// a vypis jeho klic
				std::cout << curr->data;
			}
			else { // neexistuje-li aktualni prvek (prvek je nullptr)
				// vloz do fronty jako jeho syny zase nullptr
				q.push(nullptr);
				q.push(nullptr);
				// Vypis mezeru misto jeho hodnoty
				std::cout << "  "; // lze prepsat na "xx" a bude na miste chybejiciho vrcholu psat "xx"
			}
			// vynech zase mezeru za prvkem
			std::cout << std::setw(space * 2) << " "; // cislo kterym nasobime space je maximalni pocet cislic klice
		}
		space /= 2; // zmensi mezeru na dalsi urovni na polovinu
		std::cout << std::endl; // prejdi na novy radek
	}
	std::cout << std::endl;
}