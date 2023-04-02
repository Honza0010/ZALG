namespace iterative
{
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
                result = (solution[j] != m) && (solution[k - j - 1] != m - j - 1 || m - j - 1 == -1) && (solution[k - j - 1] != m + j + 1);
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
        n_queens(int n) : n(n), solution(std::vector<int>(n, -1)) {}

        void find_solution()
        {
            int k = 0;
            while (k >= 0)
            {
                int i = solution[k] + 1;    //In the beginning of every column solution[k] == -1, therefore we add +1
                //When we step back with k-1 (the backtracking), we will start from solutio[k]+1 because we have found all safe position in this row above
                bool found = false;

                for (; i < n && !found; i++)    //If we find safe place, we can for now end this loop and go to the next column or print result
                {
                    if (is_safe(i, k))
                    {
                        solution[k] = i;
                        found = true;
                    }
                }

                if (found)  //We found safe position
                {
                    if (k == n - 1)     //If we are in the last column, we found one whole solution
                    {
                        print();
                    }
                    else {
                        k++;
                    }
                }
                else    //If we didnt find safe position, we go backwards (backtracking)
                {
                    solution[k] = -1;   //We have to free this column
                    k--;                //We step back to previous column
                }
            }
        }

    };
}