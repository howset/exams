
/*
The final version with a single starting city (index 0)
*/


#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define CITY_0 0
#define NO_PREV -1

double	distance(double x1, double y1, double x2, double y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool	all_cities_visited(bool *visited, int count)
{
	int	i = -1;

	while (++i < count)
	{
		if (!visited[i])
			return false;
	}
	return true;
}

int	count_cities(void)
{
	size_t	len;
	char	*line = NULL;
	int	count = 0;

	while (getline(&line, &len, stdin) >= 0)
	{
		count++;
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	fseek(stdin, 0L, SEEK_SET);
	return count;
}

void	get_coords(double c[][2], int count)
{
	int	i = 0;

	while (fscanf(stdin, "%lf, %lf", &c[i][0], &c[i][1]) == 2)
		i++;
}

void	init(double c[][2], bool *visited, double *min, int count)
{
	int	i = -1;
	double	aggr = 0.0;
	int	next;

	while (++i < count)
	{
		next = i + 1;
		if (i == count - 1)
			next = 0;
		aggr += distance(c[i][0], c[i][1], c[next][0], c[next][1]);
		visited[i] = false;
	}
	*min = aggr;
}

void	process(double c[][2], bool *v, double aggr, double *min, int count, int prev)
{
	if (all_cities_visited(v, count)) // base case
	{
		aggr += distance(c[prev][0], c[prev][1], c[CITY_0][0], c[CITY_0][1]);
		if (aggr < *min)
			*min = aggr;
		return ;
	}
    if (prev == NO_PREV) // optimization: first recursive call returns
    {
        v[CITY_0] = true;
        return process(c, v, 0.00, min, count, CITY_0);
    }
	int	this_one = -1;
	while (++this_one < count) // assumptions generator
	{
		if (v[this_one])
			continue ;
        double	dist = distance(c[prev][0], c[prev][1], c[this_one][0], c[this_one][1]);
		v[this_one] = true;
		process(c, v, aggr + dist, min, count, this_one);
		v[this_one] = false;
	}
}

int	main(void)
{
	int	count = count_cities();
	double	c[count][2];
	bool	visited[count];
	double	min = 0.00;

	get_coords(c, count);
	init(c, visited, &min, count);
	process(c, visited, 0.00, &min, count, NO_PREV);
	printf("%'.2f\n", min);
}
