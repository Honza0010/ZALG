#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>

class knights_problem
{
	int n;		//Size of chessboard
	std::pair<int, int> start; //Start position of the knight
	std::vector<std::vector<int>> chessboard;	//Chessboard

	std::vector<std::pair<int, int>> moves;    //Knight can make up to 8 moves depending on where he stands on the board
	std::vector<std::vector<std::pair<int, int>>> ancestors;	//This matrix stores the previous point of the current square on the path


	bool is_position_valid(int x, int y)
	{
		return x >= 0 && x < n && y >= 0 && y < n && chessboard[x][y] == -1;	//The last condition checks whether the position was visited or not
	}


	bool solve_help(int x, int y)
	{
		if (chessboard[x][y] == n * n - 1)		//If we went through all the chessboard, we necessarily are at distance n*n-1 from start
		{
			print_chessboard();		//We print the solution
			//print_solution();
			return true;	//If we want to get just one solution, otherwise we would have to return false
		}

		for (auto [move_x, move_y] : moves)		//We take all of 8 possible moves of knight
		{
			std::pair<int, int> position = { x + move_x, y + move_y };	//We calculate new position with the move
			if (is_position_valid(position.first, position.second))		//We check the new position if it is on the chessboard and still unvisited
			{
				chessboard[position.first][position.second] = chessboard[x][y] + 1;	//If position is valid, we calculate the distance
				ancestors[position.first][position.second] = { x,y };				//And we need to store the ancestors

				if (solve_help(position.first, position.second))	//It depends on if we want just one or all solutions
				{
					return true;
				}

				chessboard[position.first][position.second] = -1;
				ancestors[position.first][position.second] = { -1,-1 };
			}

			
		}

		return false;
	}


	void print_solution()		//It prints the chessboard and all ancestors
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << chessboard[i][j] << "\t";
			}
			std::cout << std::setw(30);
			for (int j = 0; j < n; j++)
			{
				std::cout << "(" << ancestors[i][j].first << "," << ancestors[i][j].second << ") ";
			}
			
		}
		std::cout << "Jedno reseni" << std::endl << std::endl;
	}


	void print_chessboard()		//It prints just chessboard
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << chessboard[i][j] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << "Jedno reseni" << std::endl << std::endl;
	}

public:
	knights_problem(int n, int x, int y) : n(n), start({x,y})
	{ 
		chessboard = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));		//All distances will be at first -1
		moves = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };		//All possible moves with the knight
		ancestors = std::vector<std::vector<std::pair<int, int>>>(n, std::vector<std::pair<int, int>>(n, { -1,-1 }));	//All ancestors will be at first (-1,-1)
		chessboard[start.first][start.second] = 0;
	}


	

	void solve()
	{
		solve_help(start.first, start.second);
	}





};