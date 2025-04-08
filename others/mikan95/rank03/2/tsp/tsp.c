#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#define MAX_CITIES 11

typedef struct
{
    float x, y;
} City;

float distance(City a, City b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float calculate_path(City *cities, int *order, int n)
{
    float total = 0;
    for (int i = 0; i < n; i++)
        total += distance(cities[order[i]], cities[order[(i + 1) % n]]);
    return total;
}

void permute(int *order, int start, int n, float *min_path, City *cities)
{
    if (start == n)
    {
        float path_len = calculate_path(cities, order, n);
        if (path_len < *min_path)
            *min_path = path_len;
        return;
    }
    for (int i = start; i < n; i++)
    {
        int temp = order[start];
        order[start] = order[i];
        order[i] = temp;

        permute(order, start + 1, n, min_path, cities);

        temp = order[start];
        order[start] = order[i];
        order[i] = temp;
    }
}

int parse_coordinates(char *line, float *x, float *y)
{
    int i = 0;
    int sign = 1;
    *x = 0;
    *y = 0;

    // Parse x coordinate
    if (line[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (line[i] >= '0' && line[i] <= '9')
    {
        *x = *x * 10 + (line[i] - '0');
        i++;
    }
    if (line[i] == '.')
    {
        i++;
        float factor = 0.1f;
        while (line[i] >= '0' && line[i] <= '9')
        {
            *x += (line[i] - '0') * factor;
            factor *= 0.1f;
            i++;
        }
    }
    *x *= sign;
    if (line[i] != ',')
        return 0;
    i++;
    sign = 1;
    if (line[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (line[i] >= '0' && line[i] <= '9')
    {
        *y = *y * 10 + (line[i] - '0');
        i++;
    }
    if (line[i] == '.')
    {
        i++;
        float factor = 0.1f;
        while (line[i] >= '0' && line[i] <= '9')
        {
            *y += (line[i] - '0') * factor;
            factor *= 0.1f;
            i++;
        }
    }
    *y *= sign;

    return 1;
}

int main()
{
    City cities[MAX_CITIES];
    int n = 0;
    char *line = NULL;
    size_t len = 0;
    while (n < MAX_CITIES && getline(&line, &len, stdin) != -1)
    {
        float x, y;
        if (!parse_coordinates(line, &x, &y))
            continue;

        cities[n].x = x;
        cities[n].y = y;
        n++;
    }
    free(line);
    if (n < 2)
    {
        return 1; // Exit silently if not enough cities
    }
    int order[MAX_CITIES];
    for (int i = 0; i < n; i++)
        order[i] = i;
    float min_path = 1e9;
    permute(order, 0, n, &min_path, cities);
    //char output[32];
    int len_out = 0;
    int int_part = (int)min_path;
    float frac_part = min_path - int_part;
    len_out += printf("%d.", int_part);
    frac_part *= 100;
    int frac = (int)frac_part;
    len_out += printf("%02d\n", frac);

    return 0;
}

//to execute: gcc -Wall -Wextra -Werror tsp.c -lm -o tsp
// cat test_tsp/filename.txt | ./tsp


// void write_result(float result)
// {
//     int int_part = (int)result;
//     int frac_part = (int)((result - int_part) * 100);

//     char buffer[32];
//     int len = 0;

//     // Convert integer part
//     if (int_part == 0)
//         buffer[len++] = '0';
//     else
//     {
//         char temp[16];
//         int temp_len = 0;
//         while (int_part > 0)
//         {
//             temp[temp_len++] = (int_part % 10) + '0';
//             int_part /= 10;
//         }
//         for (int i = temp_len - 1; i >= 0; i--)
//             buffer[len++] = temp[i];
//     }

//     // Add decimal point and fractional part
//     buffer[len++] = '.';
//     buffer[len++] = (frac_part / 10) + '0';
//     buffer[len++] = (frac_part % 10) + '0';
//     buffer[len++] = '\n';

//     write(STDOUT_FILENO, buffer, len);
// }



