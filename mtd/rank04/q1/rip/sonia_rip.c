#include <unistd.h>

int count_unbalanced(const char *str) {
    int open = 0;
    int unbalanced = 0;
    
    while (*str) {
        if (*str == '(') {
            open++;
        }
        else if (*str == ')') {
            if (open == 0)
                unbalanced++;
            else
                open--;
        }
        str++;
    }
    return unbalanced + open;
}

void    print_solution(const char *str, int *remove_pos, int remove_count) {
    int i = 0;
    
    while (str[i]) {
        int should_remove = 0;
        for (int j = 0; j < remove_count; j++) {
            if (i == remove_pos[j]) {
                should_remove = 1;
                break;
            }
        }
        if (should_remove)
            write(1, " ", 1);
        else
            write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void    check_combination(const char *str, int *remove_pos, int remove_count) {
    char temp[30];
    int i = 0;
    int j = 0;
    
    while (str[i]) {
        int should_skip = 0;
        for (int k = 0; k < remove_count; k++) {
            if (i == remove_pos[k]) {
                should_skip = 1;
                break;
            }
        }
        if (!should_skip)
            temp[j++] = str[i];
        i++;
    }
    temp[j] = '\0';
    
    if (count_unbalanced(temp) == 0)
        print_solution(str, remove_pos, remove_count);
}

void    try_combinations(const char *str, int *remove_pos, int pos, int start, int len, int remove_count) {
    if (pos == remove_count) {
        check_combination(str, remove_pos, remove_count);
        return;
    }
    
    for (int i = start; i < len; i++) {
        remove_pos[pos] = i;
        try_combinations(str, remove_pos, pos + 1, i + 1, len, remove_count);
    }
}

void    solve(const char *str) {
    int len = 0;
    while (str[len])
        len++;
    
    int remove_count = count_unbalanced(str);
    int remove_pos[30] = {0};
    
    try_combinations(str, remove_pos, 0, 0, len, remove_count);
}

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;

    char *str = argv[1];
    
    if (count_unbalanced(str) == 0) {
        while (*str)
            write(1, str++, 1);
        write(1, "\n", 1);
        return 0;
    }
    
    solve(str);
    return 0;
}