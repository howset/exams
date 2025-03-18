#include <stdio.h>
#include <ctype.h>

int main()
{
    int num = 0;          // Initialize variables
    char str[100] = {0};  // Buffer for string input
    char ch = '\0';       // Initialize character variable

    printf("Enter an integer: ");
    if (scanf("%d", &num) == 1)  // Return value of scanf indicates success
        printf("You entered: %d\n", num);
    else {
        printf("Invalid input for integer.\n");
        while (getchar() != '\n');  // Clear invalid input from the buffer
    }

    printf("Enter a string: ");
    if (scanf("%s", str) == 1)  // Return value of scanf indicates success
        printf("You entered: %s\n", str);

    printf("Enter a character: ");
    if (scanf(" %c", &ch) == 1)  // Space before %c to skip whitespace
        printf("You entered: %c\n", ch);

    return 0;
}
