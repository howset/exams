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

Authorized functions (from memory, didn't write them down):
* definitely yes: getline, sqrtf, stdin, stdout, fprintf, write
* definitely not: printf
* perhaps: fseek, ???
*/


#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define HOWMANY 7
#define EXISTS 0

double	distance(double x1, double y1, double x2, double y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	init(bool *city_visited, double *min_dist, double cities[][2], int howmany)
{
	int	i;

	i = -1;
	while (++i < howmany - 1)
	{
		city_visited[i] = false;
		if (cities[i + 1][0] >= EXISTS)
			*min_dist += distance(cities[i][0], cities[i][1], \
				cities[i + 1][0], cities[i + 1][1]);
	}
	// printf("after the loop, i is: %d\n", i);
	*min_dist += distance(cities[i][0], cities[i][1], \
			cities[0][0], cities[0][1]);
	city_visited[i] = false;
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

void	calc_dist(double cities[][2], bool *city_visited, int hm, double aggr, double *min_dist, int prev_city, int this_city)
{
	int	next_city = -1;

	city_visited[this_city] = true; // update record of visited (guarranteed to have been false)
	// increment aggr (also no harm done when prev_city == this_city)
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
		// recursive case, where city_visited[next_city] == false
		calc_dist(cities, city_visited, hm, aggr, min_dist, this_city, next_city);
	}
	// reset visitation record of this_city b4 going back
	city_visited[this_city] = false;
}

int	main(void)
{
	double	min_dist = 0;
	bool	city_visited[HOWMANY];
	double	cities[HOWMANY][2] = {
		{11.82, 24.50},
		{65.24, 22.28},
		{45.53, 42.11},
		{80.01, 19.77},
		{59.90, 82.44},
		{2.11, 17.19},
		{92.11, 7.44}};

	init(city_visited, &min_dist, cities, HOWMANY);
	// while (coords[++i][0] >= 0)
	//	fprintf(stdout, "x1: %'.2f, y1: %'.2f\n", coords[i][0], coords[i][1]);
	// fprintf(stdout, "default total distance: %'.2f\n", min_dist);
	int	i = -1;
	// while (++i < HOWMANY)
		// printf("vis_city_idx: %s\n", city_visited[i] ? "true" : "false");
	calc_dist(cities, city_visited, HOWMANY, 0.0, &min_dist, 0, 0);
	// printf("minimum distance to cover all cities: %'.2f\n", min_dist);
	printf("%'.2f\n", min_dist);
}
