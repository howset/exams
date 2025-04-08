#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct
{
	float x,y;
} City;

float	distance(City a, City b)
{
	return sqrtf((a.x -b.x)* (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
}

float	calculate_path(City *cities, int *order, int n)
{
	float total= 0;
	for(int i= 0; i<n; i++)
		total +=distance(cities[order[i]],cities[order[(i+1)%n]]);
	return total;
}

void	permute(int *order, int start, int n, float *min_path, City *cities)
{
	if(start ==n)
	{
		float path_len = calculate_path(cities, order,n);
		if(path_len < *min_path)
			*min_path= path_len;
		return;
	}
	for (int i = start; i<n; i++)
	{
		int temp = order[start];
		order[start] = order[i];
		order[i]=temp;
		permute(order,start +1,n, &*min_path,cities);
		int temp = order[start];
		order[start] = order[i];
		order[i]=temp;
	}
}

int main()
{
	FILE *input= stdin;
	City cities[11];
	int n = 0;
	while (n<11 && !feof(input))
	{
		if(fscanf(input,"%f, %f\n", &cities[n].x,&cities[n].y) !=2)
			{
				fprintf(stderr,"Error: Invalid input \n");
				return 1;
			}
		n++;
	}
	if(n<2)
	{
		fprintf(stderr, "Error: Not enough cities\n");
		return 1;
	}
	int order[11];
	for(int i = 0; i<n;i++)
		order[1] = i;
	float min_path= 1e9;
	permute(order,0,n,&min_path,cities);
	fprintf(stdout, "%.2f\n", min_path);
	return 0;
}
