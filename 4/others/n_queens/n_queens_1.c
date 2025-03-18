#include <unistd.h>
#include <stdlib.h>

/* void print_solution(int *board, int n)
{
	int i = 0;
	while (i < n)
	{
		char c = board[i] + '0';
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
} */

void print_solution(int *board, int n)
{
	int i = 0;
	while (i < n)
	{
		// Convert number to string and print with space separator
		char buf[32];
		int len = 0;
		int num = board[i];
		// Handle 0 case separately
		if (num == 0)
			buf[len++] = '0';
		else
		{
			// Convert number to string in reverse
			while (num > 0)
			{
				buf[len++] = (num % 10) + '0';
				num /= 10;
			}
			// Reverse the string
			for (int j = 0; j < len/2; j++)
			{
				char temp = buf[j];
				buf[j] = buf[len-1-j];
			buf[len-1-j] = temp;
			}
		}
		// Print number
		write(1, buf, len);
		i++;
	}
	write(1, "\n", 1);
}

int is_safe(int *board, int col, int row)
{
	int i = 0;
	while (i < col)
	{
		if (board[i] == row)
			return 0;
		if ((col - i) == abs(row - board[i]))
			return 0;
		i++;
	}
	return 1;
}

void solve_nq(int *board, int col, int n)
{
	if (col == n)
	{
		print_solution(board, n);
		return;
	}
	int row = 0;
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			solve_nq(board, col + 1, n);
		}
		row++;
	}
}

int main(int argc, char **argv)
{
	int	n;

	if (argc != 2)
		return 1;
	n = atoi(argv[1]);
	if (n <= 0)
		return 1;
	int	board[n];
	solve_nq(board, 0, n);
	return 0;
}
//gcc -Wall -Wextra -Werror -o n_queens n_queens.c
//./n_queens 4
