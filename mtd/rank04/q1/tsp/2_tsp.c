
/*
The final version which checks each city as starting city.
Proven to be unnecessary.
*/


#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

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

bool	no_cities_visited(bool *visited, int count)
{
	int	i = -1;

	while (++i < count)
	{
		if (visited[i])
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
	i = -1;
	//while (++i < count)
	//	printf("c[%d][0]: %f && c[%d][1]: %f\n", i, c[i][0], i, c[i][1]);
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

void	process(double c[][2], bool *v, double aggr, double *min, int count, int prev, int *first)
{
	if (all_cities_visited(v, count))
	{
		aggr += distance(c[prev][0], c[prev][1], c[*first][0], c[*first][1]);
		if (aggr < *min)
		{
			*min = aggr;
			printf("new min: %'.2f. Starting city: %d\n", *min, *first);
		}
		return ;
	}
	int	th = -1;
	while (++th < count)
	{
		double	dist;
		if (v[th])
			continue ;
		if (prev == -1)
		{
			*first = th;
			printf("new starting city: %d\n", *first);
		}
		else
			dist = distance(c[prev][0], c[prev][1], c[th][0], c[th][1]);
		v[th] = true;
		process(c, v, aggr + dist, min, count, th, first);
		v[th] = false;
	}
}

int	main(void)
{
	int	count = count_cities();
	double	c[count][2];
	bool	visited[count];
	double	min = 0.00;
	int	first = -1;

	get_coords(c, count);
	init(c, visited, &min, count);
	printf("%'.2f\n", min);
	process(c, visited, 0.00, &min, count, -1, &first);
	printf("%'.2f\n", min);
}
