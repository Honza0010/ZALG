#pragma once

using T = int;

class binary_tree
{
private:
	class node;

public:
	binary_tree();
	~binary_tree();

	bool empty();

	void remove_all(node* node_);

	void insert(const T& data);

	void insert_iteratively(const T& data);

	node* find(const T& data, node*& parent);

	node* find_iteratively(const T& data, node*& parent);

	void write() const;

	void stack_write();

	void remove_node(const T& data);

	void treeprint();

	void treeprint2();

	void wide_print();
	
private:
	node* root;
	unsigned int number_of_elements;
	unsigned int number_of_levels;
	
	void insert_into_subtree(const T& data, node* node_,unsigned int depth_);

	node* find_in_subtree(const T& data, node*& parent, node* node_);

	void remove_leaf(node* to_delete, node* parent);

	void remove_with_one_child(node* to_delete, node* parent);

	void remove_with_two_children(node* to_delete, node* parent);

	int getDepth(node* node_);

	void write_(node* node_) const;

	void print_lvl(int n);

	void display_lvl(node* help, int lvl, int d);
};


class binary_tree::node
{
public:
	node(const T& data);
	int getData() const;

private:
	T data;
	node* left;
	node* right;
	unsigned int depth;

	friend class binary_tree;
};