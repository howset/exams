/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s0nia_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:45:55 by s.veselova        #+#    #+#             */
/*   Updated: 2024/12/09 21:23:33 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>


int is_safe(int *board, int row, int col, int n)
{
    //Check row on the left side
    for (int i = 0; i < col; i++)
    {
        if (board[i] == row)
            return 0;
    }
    
    //Check upper diagonal on the left side
    for (int i = row - 1, j = col - 1; i >= 0 && j >=0; i--, j--)
    {
        if (board[j] == i)
            return 0;
    }
    
    //Check lower diagonal on the left side
    for (int i = row + 1, j = col - 1; i < n && j >=0; i++, j--)
    {
        if (board[j] == i)
            return 0;
    }
    return 1;
}

// Recursive function to solve N Queens
void solve_n_queens(int *board, int col, int n)
{
    // Print result if all queens are placed
    if (col == n)
    {
        for (int i = 0; i < n; i++)
            printf("%d ", board[i]);
        printf("\n");
        return ;
    }
    // Try placing queen in all rows of this column
    for (int i = 0; i < n; i++)
    {
        if (is_safe(board, i, col, n))
        {
            board[col] = i;
            solve_n_queens(board, col + 1, n);
            board[col] = -1;
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

    int board[n];
    for (int i = 0; i < n; i++)
        board[i] = -1;

    solve_n_queens(board, 0, n);
    return 0;
}