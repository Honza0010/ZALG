#include <iostream>
#include "n_queens.h"

using namespace std;


int main()
{
	n_queens q(6);

	q.find_solution(0);
	//q.print();
}