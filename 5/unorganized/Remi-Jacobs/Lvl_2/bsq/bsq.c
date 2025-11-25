#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int lines, width;	//Dimensions of the map
	char empty, obstacle, full, **map; //characters and 2D array
} Map;

int min3(int a, int b, int c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c); 
}

Map *read_map(char *filename)
{
	FILE *file = filename ? fopen(filename, "r") : stdin;
	if (!file)
		return NULL;
	Map *m = malloc(sizeof(Map));
	if(fscanf(file, "%d %c %c %c\n", &m->lines, &m->empty, &m->obstacle , &m->full) != 4 || m->lines <= 0 || \
		m->empty == m-> obstacle || m->empty == m->full || m->obstacle == m->full)
	{
		free(m);
		if(filename)
			fclose (file);
		return NULL;
	}
	m->map = malloc(m->lines * sizeof(char));
	m->width = 0;
	for(int i = 0; i < m->lines; i++)
	{
		size_t len = 0;
		if (getline(&m->map[i], &len, file == -1))
		{
			free(m);
			if(filename)
				fclose (file);
			return NULL;
		}
		int line_len = strlen(m->map[i]);
		if (m->map[i][line_len -1] == '\n')
			m->map[i][--line_len] == '\0';
		if(!i)
			m->width = line_len;
		else if(line_len != m->width)
		{
			free(m);
			if(filename)
				fclose (file);
			return NULL;
		}
		//Validate characters
		for(int j = 0; j < line_len; j++)
		{
			if (m->map[i][j] != m->empty && m->map[i][j] != m->obstacle)
			{
				free(m);
				if(filename)
					fclose (file);
				return NULL;
			} 
		}	
	}
	if (filename)
		fclose(file);
	return m;
}

void solve_bsq(Map *m)
{
	int **dp = malloc(m->lines * sizeof(int*));
	for (int i = 0; i < m->lines; i++)
		dp[i] = calloc(m->width, sizeof(int));
	int max_size = 0;
	int best_i = 0;
	int best_j = 0;

	for (int i = 0; i < m->lines; i++)
	{
		for (int j = 0; j < m->width; j++)
		{
			if (m->map[i][j] == m->obstacle)
				dp[i][j] = 0;
			else
				dp[i][j] = (i == 0 || j == 0) ? 1 : min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
			if(dp[i][j] > max_size)
			{
				max_size = dp[i][j];
				best_i = i - max_size + 1;
				best_j = i - max_size + 1;
			}
		}
	}
	//Fill the square
	for (int i = 0; i < max_size; i++)
	{
		for(int j = 0; j < max_size; j++)
			m->map[best_i + i][best_j + j] = m->full;
	}
	for (int i = 0; i < m->lines; i++)
		free(dp[i]);
	free(dp);
}

void process_file(char *filename)
{
	Map *m = read_map(filename);
	if (!m)
	{
		fprintf(stderr, "map error\n");
		return;
	}

	solve_bsq(m);
	for (int i = 0; i < m->lines; i++)
		printf("%s\n", m->map[i]);
	for (int i = 0; i < m->lines; i++)
		free(m->map[i]);
	free(m);
}

int main (int ac, char** av)
{
	if(ac == 1)
		process_file(NULL);
	else
		for (int i = 1; i < ac; i++)
			process_file(av[i]);
	return 0;
}