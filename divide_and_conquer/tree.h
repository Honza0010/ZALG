#pragma once

using T = int;




class tree
{
private:
	class node;

public:
	tree();
	~tree();

	void clear();
	

	bool empty() const;
	void insert(const T& data);
	void insert_recursively(const T& data);

	node* find_recursively(const T& data, node*& parent);
	node* find_iteratively(const T& data, node*& parent);

	void remove_node(const T& data);

	void write();
	void write_find(const T& data);


	void TREEPRINT();
	void treeprint2();

	void wide_print();
	

private:
	
	node* root;
	int number_of_nodes;
	int depth;

	void remove_all(node* node_);
	
	void insert_into_subtree(const T& data, node* node_, int depth_);
	node* find_in_subtree(const T& data, node* &parent, node* node_);

	void remove_leaf(node* deleted, node* parent);
	void remove_one_child(node* deleted, node* parent);
	void remove_two_children(node* deleted, node* parent);

	int getDepth(node* node_);
	
	void write_(node* node_, int n);

	void printlv(int n);
	void dispLV(node* p, int lv, int d);
};

class tree::node
{
public:
	node(T data);
	T getData() const;
	void setData(const T& data);
	void setDepth(const int& depth) { this->depth = depth; }
private:
	T data;
	node* left;
	node* right;

	int depth;

	friend class tree;
};