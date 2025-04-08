/*
Write a program that will read a set of city coordinates under the form '%f, %f\n' from the stdint and will print the length of the shortest possible path containing all these cities under the form %.2f

Your program should work like this:

$ cat square.txt
0.0, 0.0
0.0, 1.0
1.0, 0.0
1.0, 1.0

$ ./tsp < square.txt | cat -e
4.00$

We will not test your program with more than 11 cities.

Authorized functions:
write, sqrtf, getline, fseek, fscanf, ferror, feof, fabsf, memcpy, fprintf, fclose,
malloc, calloc, realloc, free, fopen, errno, stderr, stdin, stdout
*/


#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define FIRST_CITY 0

float	distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// the one without malloc, no leaks
// int	count_cities(void)
// {
// 	char	*line = NULL;
// 	size_t	len;
// 	int	count = 0;
// 
// 	while (getline(&line, &len, stdin) >= 0)
// 	{
// 		count++;
// 		free(line);
// 		line = NULL;
// 	}
// 	if (line)
// 		free(line);
// 	fseek(stdin, 0, SEEK_SET);
// 	return count;
// }

// with malloc, no leaks
int	count_cities(void)
{
	char	*line = malloc(sizeof(char) * 1000);
	size_t	len = 1000;
	int	count = 0;

	while (getline(&line, &len, stdin) >= 0)
		count++;
	free(line);
	fseek(stdin, 0, SEEK_SET);
	return count;
}

void	init(bool *city_visited, float *min_dist, float cities[][2], int howmany)
{
	int	i;

	i = -1;
	while (++i < howmany)
		fscanf(stdin, "%f %*s %f", &cities[i][0], &cities[i][1]);
	i = -1;
	while (++i < howmany - 1)
	{
		city_visited[i] = false;
		*min_dist += distance(cities[i][0], cities[i][1], \
				cities[i + 1][0], cities[i + 1][1]);
	}
	city_visited[i] = false;
	*min_dist += distance(cities[i][0], cities[i][1], \
			cities[FIRST_CITY][0], cities[FIRST_CITY][1]);
}

bool	all_cities_visited(bool *city_visited, int howmany)
{
	int	i = -1;

	while (++i < howmany)
	{
		if (city_visited[i] == false)
			return (false);
	}
	return (true);
}

void	calc_dist(float cities[][2], bool *city_visited, int hm, float aggr, float *min_dist, int prev_city, int this_city)
{
	int	next_city = -1;

	city_visited[this_city] = true; // update visitation record
	aggr += distance(cities[prev_city][0], cities[prev_city][1], cities[this_city][0], cities[this_city][1]);
	while (++next_city < hm)
	{
		if (all_cities_visited(city_visited, hm)) // base case
		{
			aggr += distance(cities[this_city][0], cities[this_city][1], cities[0][0], cities[0][1]);
			if (aggr < *min_dist)
				*min_dist = aggr;
			break ;
		}
		if (city_visited[next_city] || next_city == this_city)
			continue ;
		calc_dist(cities, city_visited, hm, aggr, min_dist, this_city, next_city);
	}
	city_visited[this_city] = false; // revert visitation record
}

int	main(void)
{
	float	min_dist = 0;
	int	howmany = count_cities();
	bool	city_visited[howmany];
	float	cities[howmany][2];

	init(city_visited, &min_dist, cities, howmany);
	int	i = -1;
	// while (++i < howmany)
		// fprintf(stdout, "x1: %'.2f, y1: %'.2f\n", cities[i][0], cities[i][1]);
	// fprintf(stdout, "default total distance: %'.2f\n", min_dist);
	i = -1;
	calc_dist(cities, city_visited, howmany, 0.0, &min_dist, 0, 0);
	// printf("minimum distance to cover all cities: %'.2f\n", min_dist);
	printf("%'.2f\n", min_dist);
}
