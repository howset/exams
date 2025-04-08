#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

float   distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int		main(int ac, char **av)
{
	;
}
