#include "graph.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

graph::graph()
{
	n = 10;
	positive_weights = true;
	adj_matrix = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));
	//allocate_vector();
}

graph::graph(const graph& src)
{
	this->n = src.n;
	this->positive_weights = src.positive_weights;
	this->adj_matrix = src.adj_matrix;
}

void graph::allocate_vector()
{
	adj_matrix.clear();
	adj_matrix = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));
}

//Dijkstra algorithm
std::pair<std::vector<int>, std::vector<double>> graph::dijkstra(unsigned int start)
{
	if (start < 0 || start >= n)
	{
		throw std::out_of_range("Given start is out of bounds");
	}

	std::vector<double> dist = std::vector<double>(this->n, std::numeric_limits<double>::max());	//Vector of distances, dist[i] means the distance from start into vertex i
	std::vector<int> prev = std::vector<int>(this->n, 0);	//Vector of ancestors, prev[i] means the previous vertex on the path of vertex i
	std::vector<bool> visited = std::vector<bool>(this->n, false);	//Set of unvisited vertices

	dist[start] = 0;
	prev[start] = -1;

	for (int k = 0; k < n; k++)
	{
		int index = 0;
		double min = std::numeric_limits<double>::max();
		for (int i = 0; i < n; i++)		//Here we choose the best from unvisited vertices
		{
			if (!visited[i] && dist[i] < min)	//It must be unvisited and it must have the shortest distance
			{
				index = i;
				min = dist[i];
			}
		}
		visited[index] = true;

		for (int j = 0; j < n; j++)		//Here we go through all unvisited neighbours of the vertex chosen above (index)
		{
			if (!visited[j] && adj_matrix[index][j] != 0 && dist[index] != std::numeric_limits<double>::max() && dist[index] + adj_matrix[index][j] < dist[j])	//Vertex must be unvisited, the edge between index vertex and j index must exist, the path to index vertex must be finite number and the length of the path into vertex j must be shorter from index vertex than before
			{
				dist[j] = dist[index] + adj_matrix[index][j];		//We set new length
				prev[j] = index;		//We set new previous vertex on the path from start
			}
		}
	}

	return { prev, dist };
}


//Bellman-Ford algorithm
std::pair<std::vector<int>, std::vector<double>> graph::bellman_ford(unsigned int start)
{
	if (start < 0 || start >= n)
	{
		throw std::out_of_range("Given start is out of bounds");
	}

	std::vector<double> dist = std::vector<double>(this->n, std::numeric_limits<double>::max());	//Vector of distances, dist[i] means the distance from start into vertex i
	std::vector<int> prev = std::vector<int>(this->n, 0);	//Vector of ancestors, prev[i] means the previous vertex on the path of vertex i

	dist[start] = 0;
	prev[start] = -1;

	for (int k = 0; k < n-1; k++)	//If we do relaxation operation (n-1)-times, then we get a correct result in case there was no negative cycle
	{
		for (int i = 0; i < n; i++)	//Those two nested loops are here to go through all edges of the graph
		{
			for (int j = 0; j < n; j++)
			{
				if (adj_matrix[i][j]!= 0.0 && dist[i] != std::numeric_limits<double>::max() && dist[i] + adj_matrix[i][j] < dist[j])	//We have to check if the edge exists and if the distance into vertex i has already been calculated, if those conditions are satisfied then we can check the distance into neighbours
				{
					dist[j] = dist[i] + adj_matrix[i][j];
					prev[j] = i;
				}
			}
		}
	}

	for (int i = 0; i < n; i++)		//Here we check the case whether the graph contains negative cycle or not
	{
		for (int j = 0; j < n; j++)
		{
			if (adj_matrix[i][j] != 0.0 && dist[i] != std::numeric_limits<double>::max() && dist[i] + adj_matrix[i][j] < dist[j])
			{
				throw GrafException("Graph contains negative cycle");
			}
		}
	}

	return { prev, dist };
}



void graph::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << adj_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}



graph read_graph_(const std::string& name)
{
	std::ifstream file;
	file.open(name);

	size_t n;
	std::vector<std::vector<double>> adj_matrix; //= std::vector<std::vector<double>>(n, std::vector<double>(n, 0));
	bool positive_weights = true;

	if (file.is_open())
	{
		file >> n;
		
		adj_matrix = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));

		int i = 0, j = 0;
		while (!file.eof())
		{
			double d;
			file >> d;
			adj_matrix[i][j] = d;
			if (d < 0)
			{
				positive_weights = false;
			}
			j++;
			if (j >= n)
			{
				i++;
				if (i >= n)
				{
					break;
				}
				j = 0;
			}

		}

		return graph(n, positive_weights, adj_matrix);
	}
	else
	{
		throw GrafException("File with adjacency matrix could not be open");
	}
}
