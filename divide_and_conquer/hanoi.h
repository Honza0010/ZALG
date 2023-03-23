#pragma once

#include <vector>
#include <iostream>

class hanoi
{
private:
	std::vector<std::vector<int>> tower;

	unsigned int number_of_discs;

	void move_one_disc(int source, int final_destination);

	void move_discs(int n, int source, int temp, int final_destination);

	void print_discs();
	

public:
	hanoi(unsigned int number_of_discs);

	void solve();
};