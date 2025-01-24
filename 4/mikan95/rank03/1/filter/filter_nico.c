#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *read_input(void)
{
    char *buf = malloc(1), tmp;
    int n, len = 0;

    if (!buf)
    {
        perror("Error: ");
        return (NULL);
    }
    while ((n = read(0, &tmp, 1)) > 0)
    {
        char *new_buf = realloc(buf, len + 2);
        if (!new_buf)
        {
            free(buf);
            perror("Error: ");
            return (NULL);
        }
        buf = new_buf;
        buf[len++] = tmp;
    }
    if (n < 0)
    {
        free(buf);
        perror("Error: ");
        return (NULL);
    }
    buf[len] = '\0';
    return (buf);
}

void replace(char *str, char *s)
{
    int len = strlen(s), i = 0, j;

    while (str[i])
    {
        for (j = 0; s[j] && str[i + j] == s[j]; j++);
        if (j == len)
        {
            for (j = 0; j < len; j++)
                str[i + j] = '*';
            i += len;
        }
        else
            i++;
    }
}

int main(int argc, char **argv)
{
    char *buf;

    if (argc != 2 || !argv[1][0])
        return (1);
    buf = read_input();
    if (!buf)
        return (1);
    replace(buf, argv[1]);
    printf("%s",buf);
    free(buf);
    return (0);
}


// to compile use gcc -Wall -Wextra -Werror -o program filter.c
// to run use valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program <needle> < files/huge.txt
