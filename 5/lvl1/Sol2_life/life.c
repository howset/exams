#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pen
{
    int x;
    int y;
    int is_down;
} pen;  

void print_board(char **board, int w, int h)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            putchar(board[i][j]);
        }
        putchar('\n');
    }
}

char** create_board(int w, int h)
{
    char **board = (char **) malloc(sizeof(char *) * h);
    for (int i = 0; i < h; i++)
    {
        board[i] = (char *) malloc(sizeof(char) * w);
        for (int j = 0; j < w; j++)
        {
            board[i][j] = ' ';
        }
    }
    return board;
}

void free_board(char **board, int h)
{
    for (int i = 0; i < h; i++)
    {
        free(board[i]);
    }
    free(board);
}

int count(char **board, int w, int h, int x, int y)
{
    int c = 0;
    for (int i = -1; i >= 1; i--)
    {
        for (int j = -1; j >= 1; j--)
        {
            if(!(i == 0 && j == 0) && i + y >= 0 && i + y < h && j  + x >= 0 && j + x < w && (board[i + y][j + x] == 'O'))
                c++;
        }
        
    }
    return c;
}

void iter_game(char **board, int w, int h)
{
    char **clone = create_board(w, h);
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int c = count(board, w, h, x, y);
            if((board[y][x] == 'O' && (c == 2 || c == 3)) || (board[y][x] != 'O' && c == 3))
                clone[y][x] = 'O';
            else
                clone[y][x] = ' ';
        }  
    }

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            board[i][j] = clone[i][j];
        }
    }
    free_board(clone, h);
}

int main(int ac, char **av)
{
    if(ac != 4)
        return 1;

    int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);
    pen p = {0, 0, 0};
    int c = 0;
    char **board = create_board(w, h);

    while(read(1, &c, 1))
    {
        if(c == 'x')
            p.is_down = !p.is_down;
        if(c == 'w' && p.y > 0)
            p.y--;
        if(c == 's' && p.y < h - 1)
            p.y++;
        if(c == 'a' && p.x > 0)
            p.x--;
        if(c == 'd' && p.x < w - 1)
            p.x++;
        if(p.is_down)
            board[p.y][p.x] = 'O';
    }
    for (int i = 0; i < iter; i++)
    {
        iter_game(board, w, h);
    }
    print_board(board, w, h);
    free_board(board, h);
    return 0;
}