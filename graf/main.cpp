#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
	graph g = read_graph("graf.txt");

	
	auto vysledek = g.bellman_ford(0);

	for (int i = 0; i < vysledek.first.size(); i++)
	{
		cout << i << " " << vysledek.first[i] << " " << vysledek.second[i] << endl;
	}

	cout << endl << endl;;
	auto vysledek1 = g.dijkstra(0);

	for (int i = 0; i < vysledek1.first.size(); i++)
	{
		cout << i << " " << vysledek1.first[i] << " " << vysledek1.second[i] << endl;
	}

	

}