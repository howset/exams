/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nryser <nryser@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:33:29 by nryser            #+#    #+#             */
/*   Updated: 2024/11/19 20:16:44 by nryser           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */


/* Subject:
Mimic standard scanf function
*** OLD *** Allowed functions and globals: isspace, isdigit, va_start, va_arg, va_copy, va_end
Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy, va_end
Realize only the conversations - s, d, c.
Dont have to handle the options *, m and '.
Dont have to handle the maximum field width
Dont have to handle the types modifier characters (h, hh, l...)
Dont have to handle the conversations beginning with %n$
Your function int ft_scanf(const char *format, ...);
void skip_input_space()
{
    // Input your code here
}

int scan_char(va_list ap)
{
    // Input your code here
}

int scan_int(va_list ap)
{
    // Input your code here
}

int scan_string(va_list ap)
{
    // Input your code here
}
*/


// #include <stdio.h>
// #include <stdarg.h>
// #include <ctype.h>

// // Skips whitespace characters from the input stream
// void skip_white_space(FILE *input)
// {
//     int ch;
//     while ((ch = fgetc(input)) != EOF && isspace(ch)) {
//         // Consume whitespace
//     }
//     if (ch != EOF) {
//         ungetc(ch, input);  // Push back the first non-whitespace character
//     }
// }

// // Parses an integer from the input stream
// int my_parse_int(FILE *input, va_list args)
// {
//     int num = 0;          // The resulting integer
//     int sign = 1;         // The sign of the number, default is positive
//     int ch;

//     skip_white_space(input); // Skip leading whitespace

//     ch = fgetc(input);       // Read the first character

//     if (ch == '-') {         // Check if the number is negative
//         sign = -1;           // Set sign to negative
//         ch = fgetc(input);   // Read the next character
//     } else if (ch == '+') {  // Skip optional '+' sign
//         ch = fgetc(input);
//     }

//     if (!isdigit(ch)) {      // If the next character is not a digit, fail parsing
//         if (ch != EOF) ungetc(ch, input); // Push back the invalid character
//         return 0;            // Return 0 indicating failure
//     }

//     // Parse the digits into the integer
//     while (isdigit(ch)) {
//         num = num * 10 + (ch - '0'); // Build the number digit by digit
//         ch = fgetc(input);           // Read the next character
//     }

//     if (ch != EOF) ungetc(ch, input); // Push back the last non-digit character

//     *(va_arg(args, int *)) = num * sign; // Store the result in the provided pointer
//     return 1;                            // Return 1 indicating success
// }

// // Parses a string from the input stream
// int my_parse_string(FILE *input, va_list args)
// {
//     char *str = va_arg(args, char *); // Get the pointer to the string buffer
//     int ch;

//     skip_white_space(input);          // Skip leading whitespace

//     // Read characters until EOF or whitespace
//     while ((ch = fgetc(input)) != EOF && !isspace(ch)) {
//         *str++ = (char)ch;            // Store the character in the string buffer
//     }

//     if (ch != EOF) ungetc(ch, input); // Push back the first whitespace or EOF character

//     *str = '\0';                      // Null-terminate the string
//     return 1;                         // Return 1 indicating success
// }

// // Parses a single character from the input stream
// int my_parse_char(FILE *input, va_list args)
// {
//     char *ch = va_arg(args, char *);  // Get the pointer to the character buffer

//     skip_white_space(input);          // Skip leading whitespace

//     int c = fgetc(input);             // Read the next character
//     if (c == EOF) return 0;           // If EOF, return 0 indicating failure

//     *ch = (char)c;                    // Store the character in the buffer
//     return 1;                         // Return 1 indicating success
// }

// // A simplified implementation of scanf
// int my_scanf(char *format, ...)
// {
//     va_list args;                     // Variable argument list
//     int result = 0;                   // Number of successfully parsed arguments

//     va_start(args, format);           // Initialize the argument list

// //THIS WHILE LOOP IS A FUNCTION IN THE TEST...
//     while (*format) {                 // Loop through the format string
//         if (isspace(*format)) {       // If the format contains whitespace
//             skip_white_space(stdin); // Skip whitespace in the input
//             format++;
//         } else if (*format == '%') {  // If a format specifier is found
//             format++;
//             if (*format == 'd') {     // Handle integer parsing
//                 result += my_parse_int(stdin, args);
//             } else if (*format == 's') { // Handle string parsing
//                 result += my_parse_string(stdin, args);
//             } else if (*format == 'c') { // Handle character parsing
//                 result += my_parse_char(stdin, args);
//             }
//             format++;                 // Move to the next format specifier
//         } else {
//             format++;                 // Skip unrecognized characters
//         }
//     }

//     va_end(args);                     // Clean up the argument list
//     return result;                    // Return the number of successfully parsed arguments
// }

// //Main to test (no need in the exam):
// int main()
// {
//     int num;
//     char str[100];
//     char ch;

//     // Test integer parsing
//     printf("Enter an integer: ");
//     my_scanf("%d", &num);
//     printf("You entered the integer: %d\n", num);

//     // Test string parsing
//     printf("Enter a string: ");
//     my_scanf("%s", str);
//     printf("You entered the string: %s\n", str);

//     // Test character parsing
//     printf("Enter a character: ");
//     my_scanf("%c", &ch);
//     printf("You entered the character: %c\n", ch);

//     return 0;
// }
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

// Skip whitespace characters in the input stream
void skip_white_space(FILE *input)
{
    int ch;
    while ((ch = fgetc(input)) != EOF && isspace(ch));
    if (ch != EOF) ungetc(ch, input);
}

// Parse an integer from the input stream
int my_parse_int(FILE *input, va_list args)
{
    int *num_ptr = va_arg(args, int *);
    int num = 0, sign = 1, ch, valid = 0;

    skip_white_space(input);
    if ((ch = fgetc(input)) == '-') sign = -1;
    else if (ch != '+') {
        if (!isdigit(ch)) {
            if (ch != EOF) ungetc(ch, input);
            return 0;  // Parsing failed
        }
    }

    while (isdigit(ch))
    {
        num = num * 10 + (ch - '0');
        valid = 1;
        ch = fgetc(input);
    }

    if (ch != EOF) ungetc(ch, input);
    if (!valid) return 0;  // Parsing failed
    *num_ptr = num * sign;
    return 1;
}

// Parse a string from the input stream
int my_parse_string(FILE *input, va_list args)
{
    char *str = va_arg(args, char *), ch;
    skip_white_space(input);
    while ((ch = fgetc(input)) != EOF && !isspace(ch))
        *str++ = ch;
    if (ch != EOF) ungetc(ch, input);
    *str = '\0';
    return 1;
}

// Parse a single character from the input stream
int my_parse_char(FILE *input, va_list args)
{
    char *ch = va_arg(args, char *);
    skip_white_space(input);
    int c = fgetc(input);
    if (c == EOF) return 0;
    *ch = c;
    return 1;
}

// Mimic simplified scanf function
int my_scanf(const char *format, ...)
{
    va_list args;
    int result = 0;
    va_start(args, format);
    while (*format)
    {
        if (isspace(*format)) {
            skip_white_space(stdin);
            format++;
        } else if (*format == '%' && *(++format)) {
            if (*format == 'd') result += my_parse_int(stdin, args);
            else if (*format == 's') result += my_parse_string(stdin, args);
            else if (*format == 'c') result += my_parse_char(stdin, args);
            format++;
        } else format++;
    }
    va_end(args);
    return result;
}

// Test main function
int main()
{
    int num = 0;          // Initialize variables
    char str[100] = {0};  // Buffer for string input
    char ch = '\0';       // Initialize character variable

    printf("Enter an integer: ");
    if (my_scanf("%d", &num) == 1)  // Return value of scanf indicates success
        printf("You entered: %d\n", num);
    else {
        printf("Invalid input for integer.\n");
        while (getchar() != '\n');  // Clear invalid input from the buffer
    }

    printf("Enter a string: ");
    if (my_scanf("%s", str) == 1)  // Return value of scanf indicates success
        printf("You entered: %s\n", str);

    printf("Enter a character: ");
    if (my_scanf(" %c", &ch) == 1)  // Space before %c to skip whitespace
        printf("You entered: %c\n", ch);

    return 0;
}


//to run the program:
//gcc -Wall -Wextra -Werror -o scanf_test scanf.c

//cheak leaks:
//leaks -atExit -- ./scanf_test
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./scanf_test
