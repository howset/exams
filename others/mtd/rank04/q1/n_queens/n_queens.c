#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY -1

void	print_board(int *board, int n)
{
	int	col = -1;
	while (++col < n)
		printf("%d ", board[col]);
	printf("\n");
}

/* Init the board to different and distant values on each column
 * to enable functional collisions calc in 'q_would_beef' */
void	init(int *board, int n)
{
	int	col;

	col = -1;
	while (++col < n)
		board[col] = EMPTY * (col + 1) * 1000;
}

bool	q_would_beef(int *board, int n, int q_candidate_y, int curr_col)
{
	int	prev_col;

	// no queens placed yet
	if (curr_col == 0)
		return false;
	prev_col = -1;
	while (++prev_col < curr_col)
	{	
		// Q collision on the row
		if (board[prev_col] == q_candidate_y)
			return true;
		// Q collision on the NW-SE diagonal
		if (board[prev_col] - prev_col == board[curr_col] - curr_col)
			return true;
		// Q collision on the SW-NE diagonal
		if (board[prev_col] + prev_col == board[curr_col] + curr_col)
			return true;
	}
	return false;
}

void	process(int *board, int n, int col)
{
	if (col == n)
	{
		print_board(board, n);
		return ;
	}
	int	q_candidate_y = -1;
	while (++q_candidate_y < n)
	{
		board[col] = q_candidate_y;
		if (q_would_beef(board, n, q_candidate_y, col))
		{
			board[col] = EMPTY * (q_candidate_y + 1) * 1000;
			continue ;
		}
		process(board, n, col + 1);
		board[col] = EMPTY * (q_candidate_y + 1) * 1000;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	int	n = atoi(argv[1]);
	if (n < 1 || n > 10)
		return (2);

	int	board[n];
	init(board, n);
	process(board, n, 0);
}

