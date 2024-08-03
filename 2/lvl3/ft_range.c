#include <stdlib.h>

int     absval(int n)
{
    if (n < 0)
        return (-n);
    return (n);
}

int     *ft_range(int start, int end)
{
    int arr_len;
    int *array;
    int step;
    int i;
 
    arr_len = 1 + absval(end - start);
    array = malloc(sizeof(int) * arr_len);
 
    if (start < end)
        step = 1;
    else
        step = -1;
 
    i = 0;
    while (i < arr_len)
    {
        array[i] = start;
        start = start + step;
        ++i;
    }
    return (array);
}
 
#include <stdio.h>

int      main(void)
{
 int start = -1;
 int end = 2;
 
 int *arr = ft_range(start, end);
 
 int i = 0;
 while (i < (1 + absval(end - start)))
 {
     printf("%d\n ", arr[i]);
     ++i;
 }
}