#pragma once

#include <vector>
#include <utility>
#include <iostream>

#include <queue>
#include <iomanip>
#include <algorithm>


class knight_paths		//This class is for searching the shortest path into every square from the start position
{
	int n;      //Size of chessboard
	std::pair<int, int> start; //Start position of the knight
	std::vector<std::vector<int>> chessboard;    //Chessboard

	std::vector<std::vector<std::pair<int, int>>> ancestors;	//This matrix stores the previous point of the current square on the path
	std::vector<std::pair<int, int>> moves;    //Knight can make up to 8 moves depending on where he stands on the board


	bool is_position_valid(int x, int y)
	{
		return x >= 0 && x < n && y >= 0 && y < n && chessboard[x][y] == -1;    //The last condition checks whether the position was visited or not
	}


	void print_chessboard()
	{
		std::cout << std::endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << chessboard[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}

public:
	knight_paths(int n, int x, int y) : n(n), start({ x,y })
	{
		chessboard = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));        //All distances will be at first -1
		moves = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };        //All possible moves with the knight
		ancestors = std::vector<std::vector<std::pair<int, int>>>(n, std::vector<std::pair<int, int>>(n, { -1,-1 }));	//All ancestors will be at first (-1,-1)

		chessboard[start.first][start.second] = 0;
	}

	
	void solve()
	{
		std::queue<std::pair<int, int>> q;

		q.push(start);

		while (!q.empty())
		{
			auto [x, y] = q.front();
			q.pop();

			for (auto [move_x, move_y] : moves)
			{
				std::pair<int, int> position = { x + move_x, y + move_y };

				if (is_position_valid(position.first, position.second))
				{
					chessboard[position.first][position.second] = chessboard[x][y] + 1;
					ancestors[position.first][position.second] = { x,y };
					q.push(position);
				}
			}
		}

		print_chessboard();
	}


};