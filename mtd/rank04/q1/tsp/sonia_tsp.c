#include <stdio.h>
#include <math.h>
// #include "tsp.h"
#include "sonia_tsp.h"

float distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void ft_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

float calculate_total_distance(City *cities, int *path, int n)
{
    float total = 0.0f;
    
    for (int i = 0; i < n - 1; i++)
        total += distance(cities[path[i]].x, cities[path[i]].y,
                        cities[path[i + 1]].x, cities[path[i + 1]].y);
    
    // Add distance back to start
    total += distance(cities[path[n - 1]].x, cities[path[n - 1]].y,
                    cities[path[0]].x, cities[path[0]].y);
    return total;
}

int main()
{
    City cities[MAX_CITIES];
    int path[MAX_CITIES];
    int city_count = 0;
    float min_distance = INFINITY;
    
    // Read cities
    while (city_count < MAX_CITIES)
    {
        if (scanf("%f, %f\n", &cities[city_count].x, &cities[city_count].y) != 2)
            break;
        path[city_count] = city_count;
        city_count++;
    }
    
    if (city_count == 0)
        return 1;
    
    // Try all permutations
    while (1)
    {
        float current_distance = calculate_total_distance(cities, path, city_count);
        if (current_distance < min_distance)
            min_distance = current_distance;

        // Generate next permutation
        int i = city_count - 2;
        while (i >= 0 && path[i] > path[i + 1])
            i--;
        if (i < 0)
            break;

        int j = city_count - 1;
        while (path[j] < path[i])
            j--;

        ft_swap(&path[i], &path[j]);

        // Reverse suffix
        i++;
        j = city_count - 1;
        while (i < j)
        {
            ft_swap(&path[i], &path[j]);
            i++;
            j--;
        }
    }
    printf("%.2f\n", min_distance);
    return 0;
}