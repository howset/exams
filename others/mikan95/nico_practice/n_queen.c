#include <unistd.h>
#include <stdlib.h>

void print_solution(int *board, int n)
{
	for (int i = 0; i<n; i++)
	{
		char c =board[i] + '0';
		write(1, &c,1);
		if (i < n-1)
			write(1, " ", 1);
	}
	write (1,"\n",1);
}

int is_safe(int *board, int col, int row)
{
	for(int i = 0;i < col; i++)
	{
		if(board[i] == col)
			return 0;
		if((col -i) == (row > board[i]? row-board[i] : board[i] - row))
			return 0 ;
	}
	return 1;
}

void solve(int *board, int col, int n)
{
	if (col == n)
	{
		print_solution(board, n);
		return;
	}
	for(int row = 0; row < n; row++)
	{
		if(is_safe(board, col,row))
		{
			board[col] = row;
			solve(board, col +1 ,n);
		}
	}
}

int main(int argc, char **argv)
{
	if (argc !=2)
		return 1;
	int n = atoi(argv[1]);
	if(n <= 0)
		return 1;
	int board[n];
	solve(board, 0, n);
	return 0;
}


}
