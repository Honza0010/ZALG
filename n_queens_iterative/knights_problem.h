#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <stack>
#include <queue>
#include <iomanip>
#include <algorithm>

class knights_problem
{
	int n;      //Size of chessboard
	std::pair<int, int> start; //Start position of the knight
	std::vector<std::vector<int>> chessboard;    //Chessboard

	std::vector<std::vector<std::pair<int, int>>> ancestors;	//This matrix stores the previous point of the current square on the path
	std::vector<std::pair<int, int>> moves;    //Knight can make up to 8 moves depending on where he stands on the board


	std::vector<std::vector<int>> num_of_moves;    //it checks moves which were done from the position on chessboard in method solve()


	bool is_position_valid(int x, int y)
	{
		return x >= 0 && x < n && y >= 0 && y < n && chessboard[x][y] == -1;    //The last condition checks whether the position was visited or not
	}

public:
	knights_problem(int n, int x, int y) : n(n), start({ x,y })
	{
		chessboard = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));        //All distances will be at first -1
		moves = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };        //All possible moves with the knight
		ancestors = std::vector<std::vector<std::pair<int, int>>>(n, std::vector<std::pair<int, int>>(n, { -1,-1 }));	//All ancestors will be at first (-1,-1)

		num_of_moves = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));

		chessboard[start.first][start.second] = 0;
	}

	void solve()
	{
		std::stack<std::pair<int, int>> positions; // stack of positions
		positions.push(start);	//first we insert start

		while (!positions.empty())
		{
			auto [x, y] = positions.top();		//We take first position in stack

			bool found_next_move = false;		//bool for checking whether we found next move or not

			for (int i = num_of_moves[x][y]; i < moves.size(); i++)		//matrix num_of_moves is here for remembering the index of current move which we did before (at first all squares are 0)
			{

				std::pair<int, int> position = { x + moves[i].first, y + moves[i].second};
	
				if (is_position_valid(position.first, position.second))		//We check the position after move
				{
					found_next_move = true;		//If position is valid, we found next move
					chessboard[position.first][position.second] = chessboard[x][y] + 1;		//Calculate its distance
					num_of_moves[x][y] = i + 1;		//It checks which move we did	(it indicates that next time we have to start from this index)
					positions.push(position);		//We insert this position into stack
					if (chessboard[position.first][position.second] == n * n - 1)		//Check whether we finished or not
					{
						print_chessboard();
						return;
					}
					break;
				}
			}

			if (!found_next_move)	//If there is no other move from this {x,y} position, we backtrack
			{
				chessboard[x][y] = -1;	//backtrack
				num_of_moves[x][y] = 0;		//We have to reassign the move indices because we can come to this position from another predecessor in another path searching than we came now

				positions.pop();	//We pop it from stack
			}
		}

	}



	std::vector<std::pair<int, std::pair<int, int>>> legal_moves(std::pair<int,int> pos)	//Function for searching legal moves and inserting them into vector or priority queue
	{
		std::vector<std::pair<int, std::pair<int, int>>> next_moves;	//vector of legal moves and its degrees
		for (int i = 0; i < moves.size();i++)		//In first loop we find all possible legal moves
		{
			std::pair<int, int> position = { pos.first + moves[i].first, pos.second + moves[i].second};
			if (is_position_valid(position.first, position.second))
			{
				int degree = 0;
				for (int j = 0; j < moves.size(); j++)		//In this loop find legal moves to the previous legal moves to count its degrees
				{
					std::pair<int, int> next_position = { moves[j].first + position.first, moves[j].second + position.second };
					if (is_position_valid(next_position.first, next_position.second))	//If our legal moves have "own legal moves" we calculate the degree
					{
						degree++;
					}
				}
				next_moves.emplace_back(degree, position);
			}
		}
		std::sort(next_moves.begin(), next_moves.end(), std::greater<>());	//We sort the vector into descending order because pop_back in vector is much faster than erasing first element
		return next_moves;
	}



	void warnsdorff_solve()
	{
		std::stack<std::pair<std::pair<int,int>, std::vector<std::pair<int, std::pair<int, int>>>>> positions; // stack of positions and its legal moves (stored in ordered vector) with degrees
		positions.emplace(start, legal_moves(start));	//First we insert start position and vector (priority queue) with its legal moves

		while (!positions.empty())
		{
			auto& [position, next_moves] = positions.top();		//We take the top of the stack
		
			if (chessboard[position.first][position.second] == n * n - 1)	//If we did the longest possible path, we are done
			{
				print_chessboard();
				return;
			}


			if (next_moves.empty())		//For backtrack we have to check if some position has any legal moves left, if not we backtrack and pop this position from stack
			{
				chessboard[position.first][position.second] = -1;
				positions.pop();
				continue;
			}

			std::pair<int, int> next_position = next_moves.back().second;	//We take for now the best legal move according to Warnsdorf rule
			next_moves.pop_back();											//We pop the legal move out of our priority queue represented by std::vector

			chessboard[next_position.first][next_position.second] = chessboard[position.first][position.second] + 1;	//We know the position is valid
	

			positions.emplace(next_position, legal_moves(next_position));		//We insert the next_position (our legal move of position) into stack with the priority queue of its legal moves
		}
	}

	

	void print_chessboard()
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

};



