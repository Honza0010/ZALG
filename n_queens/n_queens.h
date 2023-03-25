#pragma once

#include <vector>

class n_queens
{
	int n;
	std::vector<int> solution;      //Indices of this solution vector represents columns of the chessboard 
                                    //and the value on the specific index is the number of the row in this column
                                    //where the queen lies


    bool is_safe(int m, int k)	//m - row, k - column
    {							//This method checks, if the position in the m-th row 
                                //and in the k-th column is safe (queen is not in danger)
        if (k == 0)
        {
            return true;    //In the first column can be the queen placed everywhere
        }
        bool result = true;
        int j = 0;
        for (int j = 0; j < k && result; j++)       //We check all previous columns of the column k
        {
            result = (solution[j] != m) && (solution[k - j - 1] != m - j - 1 || m-j-1 == -1) && (solution[k - j - 1] != m + j + 1);
                    // First condition checks, if there is another queen in the m-th row
                  // second condition checks the top-left diagonal (row and column both decrease by the same number 
                    //and on that position another queen cannot be
                  //third condition checks the bottom-left diagonal of the (m,k) position (columnd decrease by the same number which row increase by)
                
            if (!result)    //If there is some collision, we return false because the position is not safe
            {
                return false;
            }
          
        }
        
        return true;
	}


    void print()
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << solution[i] << " ";
        }
        std::cout << "\n";
    }


public:
	n_queens(int n) : n(n) { solution = std::vector<int>(n, -1); }


    void find_solution(int k)   //This function recursively finds all solutions
    {
        if (k == n)     //We found solution (maximum index of vector is n-1 so all queens are placed)
        {
            print();
            return;
        }
        else
        {
            for (int i = 0; i < n; i++) // try placing the queen in every row of column k
            {
                if (is_safe(i,k))   // check if it is safe to place the queen at (i,k)
                {
                    solution[k] = i;    // place the queen at (i,k)
                    find_solution(k + 1);   // continue to the next column (k + 1)
                }
            }
        }
        if (k < n)      // clear the column (k) and backtrack to the previous column (k - 1)
        {
            solution[k] = -1;
        }
        /*
        if no safe position is found for the queen in column k, 
        the method backtracks to the previous column (k - 1) by clearing the column k 
        and trying the next possible row in column k-1.
        */
    }


  

};