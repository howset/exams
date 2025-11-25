#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int count_neighbors(int h, int w, int board[h][w], int y, int x) {
    int c = 0;
    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++) {
            if (!dy && !dx) continue;
            int ny = y + dy, nx = x + dx;
            if (ny >= 0 && ny < h && nx >= 0 && nx < w) c += board[ny][nx];
        }
    return c;
}

void simulate_generation(int h, int w, int board[h][w]) {
    int next[h][w];
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            int n = count_neighbors(h, w, board, y, x);
            next[y][x] = (board[y][x] && (n == 2 || n == 3)) || (!board[y][x] && n == 3);
        }
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            board[y][x] = next[y][x];
}

void draw_board(int h, int w, int board[h][w]) {
    int x = 0, y = 0, pen = 0;
    char c;
    while (read(0, &c, 1) == 1) {
        if (c == 'w' && y > 0) y--;
        else if (c == 's' && y < h-1) y++;
        else if (c == 'a' && x > 0) x--;
        else if (c == 'd' && x < w-1) x++;
        else if (c == 'x') pen = !pen;
        if (pen) board[y][x] = 1;
    }
}

void print_board(int h, int w, int board[h][w]) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) putchar(board[y][x] ? '0' : ' ');
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    if (argc != 4) return 1;
    int w = atoi(argv[1]), h = atoi(argv[2]), iter = atoi(argv[3]);
    int board[h][w];
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            board[y][x] = 0;
    draw_board(h, w, board);
    for (int i = 0; i < iter; i++) simulate_generation(h, w, board);
    print_board(h, w, board);
    return 0;
}