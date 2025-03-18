#include <unistd.h>
#include <stdarg.h>

void ft_put_s (char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len = *len + write(1, str++, 1);
}

void ft_put_dx (long long int nb, int *len, int base)
{
	if (nb < 0)
	{
		nb = nb * -1;
		*len = *len + write(1,"-", 1);
	}
	if (nb >= base)
		ft_put_dx((nb/base), len, base);
	*len = *len + write(1, &"0123456789abcdef"[nb%base], 1);
}

int ft_printf(const char *format, ...)
{
	int len = 0;
	va_list arg;

	va_start(arg, format);
	while (*format)
	{
		if(*format == '%' && *(format+1))
		{
			format++;
			if(*format == 's')
				ft_put_s(va_arg(arg, char*), &len);
			if(*format == 'd')
				ft_put_dx((long long int)va_arg(arg, int), &len, 10);
			if(*format == 'x')
				ft_put_dx((long long int)va_arg(arg, unsigned int), &len, 16);
		}
		else
			len = len + write(1, format, 1);
		format++;
	}
	va_end(arg);
	return(len);
}

// Main function to test the code
#include <stdio.h>
int main()
{
	int len;

	// Test 1: String
	len = ft_printf("Hello, %s!\n", "world");
	printf(" => Printed %d characters.\n", len);

	// Test 2: Decimal integer
	len = ft_printf("The number is %d.\n", 42);
	printf(" => Printed %d characters.\n", len);

	// Test 3: Negative decimal integer
	len = ft_printf("Negative number: %d.\n", -12345);
	printf(" => Printed %d characters.\n", len);

	// Test 4: Hexadecimal integer
	len = ft_printf("Hexadecimal: %x.\n", 255);
	printf(" => Printed %d characters.\n", len);

	// Test 5: Null string
	len = ft_printf("Null string: %s.\n", NULL);
	printf(" => Printed %d characters.\n", len);

	// Test 6: Multiple placeholders
	len = ft_printf("Mix: %s, %d, %x.\n", "test", 123, 255);
	printf(" => Printed %d characters.\n", len);

	return 0;
}