/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andrew_scanf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameechan <ameechan@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:57:14 by ameechan          #+#    #+#             */
/*   Updated: 2024/11/27 22:50:36 by ameechan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void	skip_white_space(FILE *input)
{
	int	c;

	c = fgetc(input);
	while (isspace(c) && c != EOF)
		c = fgetc(input);
	if (c != EOF)
		ungetc(c, input);
}

int	my_parse_int(FILE *input, va_list args)
{
	int	sign = 1;
	int	res = 0;
	int	*ptr;
	int	c;

	ptr = va_arg(args, int *);
	skip_white_space(input);
	c = fgetc(input);
	if (c == '-')
	{
		sign = -1;
		c = fgetc(input);
	}
	else if (c == '+')
		c = fgetc(input);
	if (!isdigit(c))
	{
		if(c != EOF)
			ungetc(c, input);
		return 0;
	}
	while (isdigit(c) && c != EOF)
	{
		res = res * 10 + (c - '0');
		c = fgetc(input);
	}
	if(c != EOF)
		ungetc(c, input);
	*ptr = res * sign;

	return (1);
}

int	my_parse_string(FILE *input, va_list args)
{
	char	*str;
	int		c;

	str = va_arg(args, char *);
	skip_white_space(input);

	c = fgetc(input);
	while (!isspace(c) && c != EOF)
	{
		*str = c;
		str++;
		c = fgetc(input);
	}
	if (c != EOF)
		ungetc(c, input);
	*str = '\0';

	return (1);
}

int	my_parse_char(FILE *input, va_list args)
{
	char	*ch;
	int		c;

	ch = va_arg(args, char *);

	skip_white_space(input);
	c = fgetc(input);
	if (c == EOF)
		return (0);
	*ch = c;
	return (1);
}

// A simplified implementation of scanf
int my_scanf(char *format, ...)
{
    va_list args;                     // Variable argument list
    int result = 0;                   // Number of successfully parsed arguments

    va_start(args, format);           // Initialize the argument list

//THIS WHILE LOOP IS A FUNCTION IN THE TEST...
    while (*format) {                 // Loop through the format string
        if (isspace(*format)) {       // If the format contains whitespace
            skip_white_space(stdin); // Skip whitespace in the input
            format++;
        } else if (*format == '%') {  // If a format specifier is found
            format++;
            if (*format == 'd') {     // Handle integer parsing
                result += my_parse_int(stdin, args);
            } else if (*format == 's') { // Handle string parsing
                result += my_parse_string(stdin, args);
            } else if (*format == 'c') { // Handle character parsing
                result += my_parse_char(stdin, args);
            }
            format++;                 // Move to the next format specifier
        } else {
            format++;                 // Skip unrecognized characters
        }
    }

    va_end(args);                     // Clean up the argument list
    return result;                    // Return the number of successfully parsed arguments
}

//Main to test (no need in the exam):
int main()
{
    int num;
    char str[100];
    char ch;

    // Test integer parsing
    printf("Enter an integer: ");
    my_scanf("%d", &num);
    printf("You entered the integer: %d\n", num);

    // Test string parsing
    printf("Enter a string: ");
    my_scanf("%s", str);
    printf("You entered the string: %s\n", str);

    // Test character parsing
    printf("Enter a character: ");
    my_scanf("%c", &ch);
    printf("You entered the character: %c\n", ch);

    return 0;
}
