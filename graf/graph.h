#pragma once

#include <vector>
#include <string>
#include <utility>
#include "GraphException.h"

class graph
{
public:
	graph();
	graph(size_t n, bool positive_weights ,const std::vector<std::vector<double>>& adj_matrix) : n(n), positive_weights(positive_weights), adj_matrix(adj_matrix) {}
	graph(const graph& src);

	~graph() = default;

	std::pair<std::vector<int>, std::vector<double>> dijkstra(unsigned int start);
	std::pair<std::vector<int>, std::vector<double>> bellman_ford(unsigned int start);

	void print();
private:
	void allocate_vector();


	std::vector<std::vector<double>> adj_matrix;
	size_t n; //Number of vertices

	bool positive_weights;	//Checks, whether all the weights are positive


	friend graph read_graph_(const std::string& name);
};




graph read_graph_(const std::string& name);