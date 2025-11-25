#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct 
{
	int **board;
	int h;
	int w;	
} Gameboard;


int count_neigbors(Gameboard *game, int y, int x)
{
	int count = 0;
	for(int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			if(!dy && !dx)
				continue;
			int ny = y + dy;
			int nx = x + dx;
			if(ny >= 0 && ny < game->h && nx >= 0 && nx < game->w)
				count += game->board[ny][nx];
		}
	} 
	return count;
}

void simulate_generation(Gameboard *game)
{
	int **next = malloc(game->h * sizeof(int*));
	for(int i = 0; i < game->h; i++)
		next[i] = malloc(game->w *sizeof(int));
	for(int y = 0; y < game->h; y++)
	{
		for(int x = 0; x < game->w; x++)
		{
			int n = count_neigbors(game, y, x);
			next[y][x] = (game->board[y][x] && (n == 2 || n == 3)) || (!game->board[y][x] && n == 3);
		}
	}
	for(int y = 0; y < game->h; y++)
		for(int x = 0; x < game->w; x++)
			game->board[y][x] = next[y][x];
	for(int i = 0; i < game->h; i++)
		free(next[i]);
	free(next);
}

void draw_board(Gameboard *game)
{
	int x = 0;
	int y = 0;
	int pen = 0;
	char c;
	while (read(0, &c, 1) == 1)
	{
		if (c == 'w' && y > 0)
			y--;
		else if(c == 's' && y < game->h -1)
			y++;
		else if(c == 'a' && y < game->w -1)
			x--;
		else if(c == 'd' && y < game->w -1)
			x++;
		else if(c == 'x')
			pen = !pen;
		if(pen)
			game->board[y][x] = 1;
	}
}

void print_board(Gameboard *game)
{
	for (int y = 0; y < game->h; y++)
	{
		for(int x = 0; x < game->w; x++)
			putchar(game->board[y][x] ? '0' : ' ');
		putchar('\n');
	}
}

int main(int ac, char** av)
{
	if (ac != 4)
		return 1;
	Gameboard game;
	game.w = atoi(av[1]);
	game.h = atoi(av[2]);
	int iter = atoi(av[3]);
	game.board = malloc(game.h * sizeof(int*));
	for (int i = 0; i < game.h; i++)
	{
		game.board[i] = malloc (game.w * sizeof(int));
		for (int j = 0; j < game.w; j++)
			game.board[i][j] = 0;
	}
	draw_board(&game);
	for(int i = 0; i < iter; i++)
		simulate_generation(&game);
	print_board(&game);
	for(int i = 0; i < game.h; i++)
		free(game.board[i]);
	free(game.board);
	return 0;
}
