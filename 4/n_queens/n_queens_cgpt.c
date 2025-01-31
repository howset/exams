#include <stdio.h>
#include <stdlib.h>

void print_solution(int *board, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d", board[i]);
    printf("\n");
}

int is_safe(int *board, int row, int col)
{
    for (int i = 0; i < col; i++)
    {
        // Check if another queen is in the same row or diagonal
        if (board[i] == row || abs(board[i] - row) == abs(i - col))
            return 0;
    }
    return 1;
}

void solve_n_queens(int *board, int col, int n)
{
    if (col == n) // Base case: all queens placed
    {
        print_solution(board, n);
        return;
    }

    for (int row = 0; row < n; row++) 
    {
        if (is_safe(board, row, col)) 
        {
            board[col] = row; // Place queen in this row
            solve_n_queens(board, col + 1, n); // Recur for next column
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    int n = atoi(argv[1]);
    if (n <= 0)
        return 1;

    int *board = (int *)malloc(n * sizeof(int));
    if (!board)
        return 1;

    solve_n_queens(board, 0, n);

    free(board);
    return 0;
}
