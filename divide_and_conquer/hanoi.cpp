#include "hanoi.h"



hanoi::hanoi(unsigned int number_of_discs)
	:number_of_discs(number_of_discs)
{
	tower.resize(3);

	for (int i = number_of_discs; i > 0; i--)
	{
		tower[0].push_back(i);
	}
}



void hanoi::move_one_disc(int source, int final_destination)
{
	int disc = tower[source].back();
	tower[source].pop_back();
	tower[final_destination].push_back(disc);
}

void hanoi::move_discs(int n, int source, int temp, int final_destination)
{
	if (n == 1)
	{
		move_one_disc(source, final_destination);
	}
	else
	{
		move_discs(n - 1, source, final_destination, temp);
		move_one_disc(source, final_destination);
		move_discs(n - 1, temp, source, final_destination);
	}
}

void hanoi::print_discs()
{
	std::cout << "A: ";
	for (int i = 0; i < tower[0].size(); i++)
	{
		std::cout << tower[0][i] << " ";
	}
	std::cout << "\n";

	std::cout << "B: ";
	for (int i = 0; i < tower[1].size(); i++)
	{
		std::cout << tower[1][i] << " ";
	}
	std::cout << "\n";

	std::cout << "C: ";
	for (int i = 0; i < tower[2].size(); i++)
	{
		std::cout << tower[2][i] << " ";
	}
	std::cout << "\n";
}


void hanoi::solve()
{
	print_discs();
	move_discs(number_of_discs, 0, 1, 2);
	print_discs();
}