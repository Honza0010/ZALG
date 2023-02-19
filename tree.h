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

	void write() const;
	void write_find(const T& data);

	void remove_node(const T& data);
	
	
private:
	
	node* root;
	

	void remove_all(node* node_);
	void write_(node* node_, int n) const;
	void insert_into_subtree(const T& data, node* node_);
	node* find_in_subtree(const T& data, node* &parent, node* node_);

	void remove_leaf(node* deleted, node* parent);
	void remove_one_child(node* deleted, node* parent);
	void remove_two_children(node* deleted, node* parent);
};

class tree::node
{
public:
	node(T data);
	T getData() const;
	void setData(const T& data);
private:
	T data;
	node* left;
	node* right;

	friend class tree;
};