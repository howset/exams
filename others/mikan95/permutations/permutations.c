#include <stdlib.h>
#include <unistd.h>

void print_string(char *str)
{
    while (*str)
        write(1, str++, 1);
    write(1, "\n", 1);
}

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void generate_permutations(char *str, int start, int end)
{
    if (start == end)
    {
        print_string(str);
        return;
    }
    for (int i = start; i <= end; i++)
    {
        swap(&str[start], &str[i]);
        generate_permutations(str, start + 1, end);
        swap(&str[start], &str[i]);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int len = 0;
    while (argv[1][len])
        len++;
    generate_permutations(argv[1], 0, len - 1);
    return 0;
}
