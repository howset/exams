/*
Test like this to confirm the fixed N results for n queens. Modify N to liking

N=8
RES=$(./n_queens $N | wc -l); N1=$(expr $N + 1); expr $RES / $N1

Board	Total Solutions
1x1	1
2x2	0
3x3	0
4x4	2
5x5	10
6x6	4
7x7	40
8x8	92
9x9	352
10x10	724

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void	print_board(int n, int *board)
{
	int	y = -1;
	int	x;
	
	while (++y < n)
	{
		x = -1;
		while (++x < n)
		{
			if (board[y] == x)
				printf("Q");
			else
				printf("_");
		}
		printf("\n");
	}
	printf("\n");
}

bool	are_q_beefing(int n, int *board, int rows)
{
	int	y = -1;
	int	next;

	if (board[0] < 0)
		return (false);
	while (++y < rows)
	{
		next = -1;
		while (++next < n)
		{
			if (y == next)
				continue ;
			if (board[y] == board[next]) // same column
				return (true);
			if (board[y] - y == board[next] - next) // SE, NW
				return (true);
			if (board[y] + y == board[next] + next) // NE, SW
				return (true);
		}
	}
	return (false);
}

void	backtrack_queens(int n, int *board, int y, int x)
{
	if (y == n) // base case
	{
		// printf("here checking board\n");
		if (!are_q_beefing(n, board, n))
			print_board(n, board);
		return ;
	}
	if (x == n)
		return ;
	if (are_q_beefing(n, board, x))
		return ;
	else
	{
		int	i = -1;
		// printf("y: %d, x: %d\n", y, x);
		while (++i < n)
		{
			board[y] = i;
			backtrack_queens(n, board, y + 1, 0);
		}
	}
}

int	main(int argc, char **argv)
{
	int	n;
	int	i = -1;
	int	rdm = -1234;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	if (n < 1 || n > 10)
		return (1);
	printf("n: %d\n", n);
	int	board[n];
	while (++i < n)
	{
		rdm -= 1000;
		board[i] = rdm;
	}
	backtrack_queens(n, board, 0, 0);
}
