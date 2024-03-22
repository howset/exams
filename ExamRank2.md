# Exam Rank 2

## Lvl 1
### first_word
```
Assignment name  : first_word
Expected files   : first_word.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays its first word, followed by a
newline.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or if there are no words, simply display
a newline.

Examples:

$> ./first_word "FOR PONY" | cat -e
FOR$
$> ./first_word "this        ...    is sparta, then again, maybe    not" | cat -e
this$
$> ./first_word "   " | cat -e
$
$> ./first_word "a" "b" | cat -e
$
$> ./first_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
$>
```

<details>
  <summary>Answer first_word</summary>
  
```c
#include <unistd.h>

int main (int argc, char **argv)
{
	int i = 0;
	
	if (argc == 2)
	{
		while (argv[1][i] == 32 || argv[1][i] == 9)
			i++;
		while ((argv[1][i] != 32 && argv[1][i] != 9) && argv[1][i])
		{
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
```
  
</details>

---

### fizzbuzz
```
Assignment name  : fizzbuzz
Expected files   : fizzbuzz.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that prints the numbers from 1 to 100, each separated by a
newline.

If the number is a multiple of 3, it prints 'fizz' instead.

If the number is a multiple of 5, it prints 'buzz' instead.

If the number is both a multiple of 3 and a multiple of 5, it prints 'fizzbuzz' instead.

Example:

$>./fizzbuzz
1
2
fizz
4
buzz
fizz
7
8
fizz
buzz
11
fizz
13
14
fizzbuzz
[...]
97
98
fizz
buzz
$>
```
<details>
  <summary>Answer fizzbuzz</summary>

```c
#include <unistd.h>

void	ft_putnbr(int nb)
{
	if (nb > 9)
		ft_putnbr(nb / 10);
	write(1, &"0123456789"[nb % 10], 1);
}

int main(void)
{
	int i = 1;

	while(i <= 100)
	{
		if(i % 3 == 0 && i % 5 == 0)
			write(1, "fizzbuzz", 8);
		else if(i % 5 == 0)
			write(1, "buzz", 4);
		else if(i % 3 == 0)
			write(1, "fizz", 4);
		else
			ft_putnbr(i);
		i++;
		write(1, "\n", 1);
	}
	return(0);
}

```
  
</details>

---

### ft_putstr
```
Assignment name  : ft_putstr
Expected files   : ft_putstr.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a function that displays a string on the standard output.

The pointer passed to the function contains the address of the string's first
character.

Your function must be declared as follows:

void	ft_putstr(char *str);
```
<details>
  <summary>Answer ft_putstr</summary>
  
```c
#include <unistd.h>

void	ft_putstr(char *str)
{
	int	i = 0;

	while (str[i])
		write(1, &str[i++], 1);
}
```
  
</details>

---

### ft_strcpy
```
Assignment name  : ft_strcpy
Expected files   : ft_strcpy.c
Allowed functions:
--------------------------------------------------------------------------------

Reproduce the behavior of the function strcpy (man strcpy).

Your function must be declared as follows:

char    *ft_strcpy(char *s1, char *s2);
```
<details>
  <summary>Answer ft_strcpy</summary>
  
```c
char	*ft_strcpy(char *s1, char *s2)
{
	int i = 0;
	
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
```
  
</details>

---

### ft_strlen
```
Assignment name  : ft_strlen
Expected files   : ft_strlen.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that returns the length of a string.

Your function must be declared as follows:

int	ft_strlen(char *str);
```
<details>
  <summary>Answer ft_strlen</summary>
  
```c
int ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}
```
  
</details>

---

### ft_swap
```
Assignment name  : ft_swap
Expected files   : ft_swap.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that swaps the contents of two integers the adresses of which
are passed as parameters.

Your function must be declared as follows:

void	ft_swap(int *a, int *b);
```
<details>
  <summary>Answer ft_swap</summary>
  
```c
void	ft_swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
```
  
</details>

---

### repeat_alpha
```
Assignment name  : repeat_alpha
Expected files   : repeat_alpha.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program called repeat_alpha that takes a string and display it
repeating each alphabetical character as many times as its alphabetical index,
followed by a newline.

'a' becomes 'a', 'b' becomes 'bb', 'e' becomes 'eeeee', etc...

Case remains unchanged.

If the number of arguments is not 1, just display a newline.

Examples:

$>./repeat_alpha "abc"
abbccc
$>./repeat_alpha "Alex." | cat -e
Alllllllllllleeeeexxxxxxxxxxxxxxxxxxxxxxxx.$
$>./repeat_alpha 'abacadaba 42!' | cat -e
abbacccaddddabba 42!$
$>./repeat_alpha | cat -e
$
$>
$>./repeat_alpha "" | cat -e
$
$>
```
<details>
  <summary>Answer repeat_alpha</summary>
  
```c
#include <unistd.h>

void    ft_putchar_n(char c, int i)
{
    while (i > 0)
    {
        write(1, &c, 1);
        --i;
    }
}

void    repeat_alpha(char *str)
{
    while (*str != '\0')
    {
        if (*str >= 'a' && *str <= 'z')
            ft_putchar_n(*str, *str + 1 - 'a');
        else if (*str >= 'A' && *str <= 'Z')
            ft_putchar_n(*str, *str + 1 - 'A');
        else
            write(1, str, 1);
        ++str;
    }
}

int main(int ac, char **av)
{
    if (ac == 2)
        repeat_alpha(av[1]);
    
    write(1, "\n", 1);
    return (0);
}
```
  
</details>

---

### rev_print
```
Assignment name  : rev_print
Expected files   : rev_print.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string, and displays the string in reverse
followed by a newline.

If the number of parameters is not 1, the program displays a newline.

Examples:

$> ./rev_print "zaz" | cat -e
zaz$
$> ./rev_print "dub0 a POIL" | cat -e
LIOP a 0bud$
$> ./rev_print | cat -e
$

```
<details>
  <summary>Answer rev_print</summary>
  
```c
#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	i = 0;

	if (argc == 2)
	{
		while (argv[1][i])
			i += 1;
		while (i)
			write(1, &argv[1][--i], 1);
	}
	write(1, "\n", 1);
	return (0);
}
```
  
</details>

---

### rot_13
```
Assignment name  : rot_13
Expected files   : rot_13.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it, replacing each of its
letters by the letter 13 spaces ahead in alphabetical order.

'z' becomes 'm' and 'Z' becomes 'M'. Case remains unaffected.

The output will be followed by a newline.

If the number of arguments is not 1, the program displays a newline.

Example:

$>./rot_13 "abc"
nop
$>./rot_13 "My horse is Amazing." | cat -e
Zl ubefr vf Nznmvat.$
$>./rot_13 "AkjhZ zLKIJz , 23y " | cat -e
NxwuM mYXVWm , 23l $
$>./rot_13 | cat -e
$
$>
$>./rot_13 "" | cat -e
$
$>
```
<details>
  <summary>Answer rot_13</summary>
  
```c
#include <unistd.h>

int	main(int argc, char **argv)
{
	int i = 0;

	if (argc > 1)
	{
		while(argv[1][i])
		{
			if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
				argv[1][i] = (argv[1][i] - 'a' + 13) % 26 + 'a';
			else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
					argv[1][i] = (argv[1][i] - 'A' + 13) % 26 + 'A';
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```
  
</details>

---

### rotone
```
Assignment name  : rotone
Expected files   : rotone.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it, replacing each of its
letters by the next one in alphabetical order.

'z' becomes 'a' and 'Z' becomes 'A'. Case remains unaffected.

The output will be followed by a \n.

If the number of arguments is not 1, the program displays \n.

Example:

$>./rotone "abc"
bcd
$>./rotone "Les stagiaires du staff ne sentent pas toujours tres bon." | cat -e
Mft tubhjbjsft ev tubgg of tfoufou qbt upvkpvst usft cpo.$
$>./rotone "AkjhZ zLKIJz , 23y " | cat -e
BlkiA aMLJKa , 23z $
$>./rotone | cat -e
$
$>
$>./rotone "" | cat -e
$
$>
```
<details>
  <summary>Answer rotone</summary>
  
```c
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	rotone(char *s)
{
	while (*s)
	{
		if ((*s >= 'A' && *s <= 'Y') || (*s >= 'a' && *s <= 'y'))
			ft_putchar(*s + 1);
		else if (*s == 'Z' || *s == 'z')
			ft_putchar(*s - 25);
		else
			ft_putchar(*s);
		++s;
	}
}

int		main(int ac, char **av)
{
	if (ac == 2)
		rotone(av[1]);
	ft_putchar('\n');
	return (0);
}
```
  
</details>

---

### search_and_replace
```
Assignment name  : search_and_replace
Expected files   : search_and_replace.c
Allowed functions: write, exit
--------------------------------------------------------------------------------

Write a program called search_and_replace that takes 3 arguments, the first
arguments is a string in which to replace a letter (2nd argument) by
another one (3rd argument).

If the number of arguments is not 3, just display a newline.

If the second argument is not contained in the first one (the string)
then the program simply rewrites the string followed by a newline.

Examples:
$>./search_and_replace "Papache est un sabre" "a" "o"
Popoche est un sobre
$>./search_and_replace "zaz" "art" "zul" | cat -e
$
$>./search_and_replace "zaz" "r" "u" | cat -e
zaz$
$>./search_and_replace "jacob" "a" "b" "c" "e" | cat -e
$
$>./search_and_replace "ZoZ eT Dovid oiME le METol." "o" "a" | cat -e
ZaZ eT David aiME le METal.$
$>./search_and_replace "wNcOre Un ExEmPle Pas Facilw a Ecrirw " "w" "e" | cat -e
eNcOre Un ExEmPle Pas Facile a Ecrire $
```
<details>
  <summary>Answer search_and_replace</summary>
  
```c
#include <unistd.h>

int main(int argc, char **argv)
{
	int i = 0;

	if (argc == 4 && !argv[2][1] & !argv[3][1])
	{
		while (argv[1][i]!='\0')
		{
			if (argv[1][i]==argv[2][0])
			{
				argv[1][i] = argv[3][0];
			}
			write (1, &argv[1][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
}
```
  
</details>

---

### ulstr
```
Assignment name  : ulstr
Expected files   : ulstr.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and reverses the case of all its letters.
Other characters remain unchanged.

You must display the result followed by a '\n'.

If the number of arguments is not 1, the program displays '\n'.

Examples :

$>./ulstr "L'eSPrit nE peUt plUs pRogResSer s'Il staGne et sI peRsIsTent VAnIte et auto-justification." | cat -e
l'EspRIT Ne PEuT PLuS PrOGrESsER S'iL STAgNE ET Si PErSiStENT vaNiTE ET AUTO-JUSTIFICATION.$
$>./ulstr "S'enTOuRer dE sECreT eSt uN sIGnE De mAnQuE De coNNaiSSanCe.  " | cat -e
s'ENtoUrER De SecREt EsT Un SigNe dE MaNqUe dE COnnAIssANcE.  $
$>./ulstr "3:21 Ba  tOut  moUn ki Ka di KE m'en Ka fe fot" | cat -e
3:21 bA  ToUT  MOuN KI kA DI ke M'EN kA FE FOT$
$>./ulstr | cat -e
$
```
<details>
  <summary>Answer ulstr</summary>
  
```c
#include <unistd.h>

int		main(int	argc, char **argv)
{
	int	i = 0;

	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
				argv[1][i] -= 32;
			else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
				argv[1][i] += 32;
			write(1, &argv[1][i], 1);
			i++;	
		}
	}
	write(1, "\n", 1);
}
```
  
</details>

---
---

## Lvl 2

### alpha_mirror
```
Assignment name  : alpha_mirror
Expected files   : alpha_mirror.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program called alpha_mirror that takes a string and displays this string
after replacing each alphabetical character by the opposite alphabetical
character, followed by a newline.

'a' becomes 'z', 'Z' becomes 'A'
'd' becomes 'w', 'M' becomes 'N'

and so on.

Case is not changed.

If the number of arguments is not 1, display only a newline.

Examples:

$>./alpha_mirror "abc"
zyx
$>./alpha_mirror "My horse is Amazing." | cat -e
Nb slihv rh Znzarmt.$
$>./alpha_mirror | cat -e
$
$>
```

<details>
  <summary>Answer alpha_mirror gitbook</summary>
  
```c
#include <unistd.h>

int main(int ac, char *av[])
{
    int i;
    
    if (ac == 2)
    {
        i = 0;
        while (av[1][i])
        {
            if (av[1][i] >= 65 && av[1][i] <= 90)
            /* we remove the ASCII code of the letter from the ASCII
             * code of the last upper-case letter, then add the ASCII
             * code of the first upper-case letter
             * 90 - 65(A) = 35, 35 + 65 = 90(Z)
             * 90 - 66(B) = 34, 34 + 65 = 89(Y)
             */ 
                av[1][i] = 90 - av[1][i] + 65;
            else if (av[1][i] >= 97 && av[1][i] <= 122)
            /* we remove the ASCII code of the letter from the ASCII
             * code of the last lower-case letter, then add the ASCII
             * code of the first lower-case letter
             * 122 - 97(a) = 35, 35 + 97 = 122(z)
             * 122 - 98(b) = 34, 34 + 97 = 121(y)
             */ 
                av[1][i] = 122 - av[1][i] + 97;
            /* finally, we can writethe current character to the screen
             */
            write(1, &av[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
}
```
</details>

<details>
  <summary>Answer alpha_mirror pasqualerossi</summary>
  
```c
#include <unistd.h>

int main(int argc, char **argv)
{
	int i = 0;

	if (argc == 2)
	{
		while(argv[1][i]) 
		{
			if(argv[1][i] >= 65 && argv[1][i] <= 90)
			{	
				argv[1][i] = 90 - argv[1][i] + 65;
			}
			else if (argv[1][i] >= 97 && argv[1][i] <= 122)
			{
				argv[1][i] = 122-argv[1][i] + 97;
			}
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write (1,"\n",1);
}		
```
</details>

<details>
  <summary>Answer alpha_mirror emreakdik</summary>
  
```c
#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 2)
	{
		while (av[1][i] != '\0')
		{
			if (av[1][i] >= 'a' && av[1][i] <= 'z')
				av[1][i] = 219 - av[1][i];
			else if (av[1][i] >= 'A' && av[1][i] <= 'Z')
				av[1][i] = 155 - av[1][i];
			write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
```
</details>

---

### camel_to_snake
```
Assignment name  : camel_to_snake
Expected files   : camel_to_snake.c
Allowed functions: malloc, realloc, write
--------------------------------------------------------------------------------

Write a program that takes a single string in lowerCamelCase format
and converts it into a string in snake_case format.

A lowerCamelCase string is a string where each word begins with a capital letter
except for the first one.

A snake_case string is a string where each word is in lower case, separated by
an underscore "_".

Examples:
$>./camel_to_snake "hereIsACamelCaseWord"
here_is_a_camel_case_word
$>./camel_to_snake "helloWorld" | cat -e
hello_world$
$>./camel_to_snake | cat -e
$
```

<details>
  <summary>Answer camel_to_snake gitbook</summary>
  
```c
#include <unistd.h>

int main(int ac, char *av[])
{
    int i;
    
    if (ac == 2)
    {
        i = 0;
        /* looping over the whole string
         */
        while (av[1][i])
        {
            /* if we encounter an upper-case letter
             * we have to make it lower-case and write a _ before it
             */
            if (av[1][i] >= 65 && av[1][i] <= 90)
            {
                /* here, we change the upper-case letter to its
                 * corresponding lower-case letter
                 */
                av[1][i] += 32;
                /* we write a _ to the screen
                 */
                write(1, "_", 1);
            }
            /* then we can write the current character, changed or not
             */
            write(1, &av[1][i], 1);
            i++;
        }
    }
    /* finally we can write the newline
     */
    write(1, "\n", 1);
}
```
</details>

<details>
  <summary>Answer camel_to_snake pasqualerossi</summary>
  
```c
#include <unistd.h>

int main(int argc, char **argv)
{
	int i = 0;

	if (argc == 2)
	{
		while(argv[1][i])
		{
			if(argv[1][i] >= 65 && argv[1][i] <= 90)
			{
				argv[1][i] = argv[1][i] + 32;
				write (1, "_", 1);
			}
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
}
```
</details>

<details>
  <summary>Answer camel_to_snake emreakdik</summary>
  
```c
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		for (int i = 0; argv[1][i]; i += 1)
		{
			if (argv[1][i] >= 'A' 
			&& argv[1][i] <= 'Z')
			{
				write(STDOUT_FILENO, "_", 1);
				argv[1][i] += 32;
			}
			write(STDOUT_FILENO, &argv[1][i], 1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	return EXIT_SUCCESS;
}
```
</details>

---

### do_op
```
Assignment name  : do_op
Expected files   : *.c, *.h
Allowed functions: atoi, printf, write
--------------------------------------------------------------------------------

Write a program that takes three strings:
- The first and the third one are representations of base-10 signed integers
  that fit in an int.
- The second one is an arithmetic operator chosen from: + - * / %

The program must display the result of the requested arithmetic operation,
followed by a newline. If the number of parameters is not 3, the program
just displays a newline.

You can assume the string have no mistakes or extraneous characters. Negative
numbers, in input or output, will have one and only one leading '-'. The
result of the operation fits in an int.

Examples:

$> ./do_op "123" "*" 456 | cat -e
56088$
$> ./do_op "9828" "/" 234 | cat -e
42$
$> ./do_op "1" "+" "-43" | cat -e
-42$
$> ./do_op | cat -e
$
```

<details>
  <summary>Answer do_op gitbook</summary>
  
```c
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
    /* checking the number of arguments
     */
    if (ac == 4)
    {
        /* we then switch over the operator (av[2][0])
         */
        switch(av[2][0])
        {
            /* if the operator is + we simply make an
             * addition and print the result to the screen
             */
            case '+':
                printf("%d", atoi(av[1]) + atoi(av[3]));
                break;
            /* if the operator is - we simply make a
             * substraction and print the result to the screen
             */
            case '-':
                printf("%d", atoi(av[1]) - atoi(av[3]));
                break;
            /* if the operator is * we simply make a
             * multiplication and print the result to the screen
             */
            case '*':
                printf("%d", atoi(av[1]) * atoi(av[3]));
                break;
            /* if the operator is / we simply make a
             * divisions and print the result to the screen
             */            
            case '/':
                printf("%d", atoi(av[1]) / atoi(av[3]));
                break;
            /* if the operator is % we simply make a
             * modulo and print the result to the screen
             */
            case '%':
                printf("%d", atoi(av[1]) % atoi(av[3]));
                break;
        }
    }
    /* finally, we write a newline
     */
    printf("\n");
}
```
</details>

<details>
  <summary>Answer do_op pasqualerossi</summary>
  
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc == 4)
	{
		if (argv[2][0] == '+')
			printf("%d", (atoi(argv[1]) + atoi(argv[3])));
		if (argv[2][0] == '-')
			printf("%d", (atoi(argv[1]) - atoi(argv[3])));
		if (argv[2][0] == '*')
			printf("%d", (atoi(argv[1]) * atoi(argv[3])));
		if (argv[2][0] == '/')
			printf("%d", (atoi(argv[1]) / atoi(argv[3])));
		if (argv[2][0] == '%')
			printf("%d", (atoi(argv[1]) % atoi(argv[3])));
	}
	printf("\n");
	return (0);
}
```
</details>

<details>
  <summary>Answer do_op emreakdik</summary>
  
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int	n1 = 0;
	int n2 = 0;
	int	res = 0;

	if (ac == 4)
	{
		n1 = atoi(av[1]);
		n2 = atoi(av[3]);
		if (av[2][0] == '+')
			res = n1 + n2;
		else if (av[2][0] == '-')
			res = n1 - n2;
		else if (av[2][0] == '*')
			res = n1 * n2;
		else if (av[2][0]== '/')
			res = n1 / n2;
		else if (av[2][0] == '%')
			res = n1 % n2;
		printf("%d\n", res);
	}
	else
		write(1, "\n", 1);
}
```
</details>

---

### ft_atoi
```
Assignment name  : ft_atoi
Expected files   : ft_atoi.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that converts the string argument str to an integer (type int)
and returns it.

It works much like the standard atoi(const char *str) function, see the man.

Your function must be declared as follows:

int	ft_atoi(const char *str);
```

<details>
  <summary>Answer ft_atoi gitbook</summary>
  
```c
/* this function returns 1 if the character is one 
 * of the "space" character or 0 if it is not
 */
int ft_isspace(int c)
{
    return ((c >= 9 && c <= 13) || c == 32 ? 1 : 0);
}

/* this function returns 1 if the character is a digit 0-9
 * and 0 if the character is not a digit 0-9
 */
int ft_isdigit(int c)
{
    return (c >= 48 && c <= 57 ? 1 : 0);
}

int ft_atoi(const char *str)
{
    int res = 0;
    int i = 0;
    int s = 1;
    
    /* skipping all the space characters 
    */
    while (ft_isspace(str[i]))
        i++;
    /* if there is a - we set the sign to -1 and we go to
     * the next character
     */
    if (str[i] == '-')
    {
        s = -1;
        i++;
    }
    /* while the number is a digit, we convert it to an int
     */
    while (ft_isdigit(str[i]))
    {
        res *= 10;
        res += str[i] - 48;
        i++;
    }
    /* at the end, we multiply the number by the sign variable
     * and we finally return the int number
     */
    return (res *= s);
}
```
</details>

<details>
  <summary>Answer ft_atoi pasqualerossi</summary>
  
```c
int	ft_atoi(char *str)
{
	int result = 0;
	int sign = 1;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
        	str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}
```
</details>

<details>
  <summary>Answer ft_atoi emreakdik</summary>
  
```c
#include <stdio.h>

int     ft_atoi(const char *str)
{
	int	nbr;
	int sig;
	int	i;

	nbr = 0;
	sig = 1;
	i = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sig = -1;
		i += 1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nbr = (nbr * 10) + (str[i++] - '0');
	return (nbr * sig);
}

/*
int	ft_atoi(const char *str);
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    (void)argc;
    printf("ft_atoi(\"%s\") = %d\n", argv[1], ft_atoi(argv[1]));
    return(0);
}
*/
```
</details>

---

### ft_strcmp
```
Assignment name  : ft_strcmp
Expected files   : ft_strcmp.c
Allowed functions:
--------------------------------------------------------------------------------

Reproduce the behavior of the function strcmp (man strcmp).

Your function must be declared as follows:

int    ft_strcmp(char *s1, char *s2);

--------------------------------------------------------------------------------
STRCMP(3) (simplified)
NAME
    strcmp -- compare strings
SYNOPSIS
    #include <string.h>
    int strcmp(const char *s1, const char *s2);
DESCRIPTION
    The strcmp() and strncmp() functions lexicographically compare the null-
terminated strings s1 and s2.
RETURN VALUES
     The strcmp() and strncmp() functions return an integer greater than,
 equal to, or less than 0, according as the string s1 is greater than,
 equal to, or less than the string s2.  The comparison is done using
 unsigned characters, so that ‘\200’ is greater than ‘\0’.
```

<details>
  <summary>Answer ft_strcmp gitbook</summary>
  
```c
int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
    // looping over both string while both of them are equal
    // and at least one of them is not finished
    while ((s1[i] || s2[i]) && s1[i] == s2[i])
        i++;
    // when we can't loop anymore, we return the substraction
    // of the last compared characters in both string, this will
    // result in either a negative, zero or positive value
    return (s1[i] - s2[i]);
}
```
</details>

<details>
  <summary>Answer ft_strcmp pasqualerossi</summary>
  
```c
#include <stdio.h>

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	
	while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{	
		i++;
	}
	return (s1[i] - s2[i]);
}
```
</details>

<details>
  <summary>Answer ft_strcmp emreakdik</summary>
  
```c
#include <stdio.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

/* int    ft_strcmp(char *s1, char *s2);
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc == 3)
        printf("ft_strcmp(\"%s\", \"%s\") = %d\n", argv[1], argv[2], ft_strcmp(argv[1], argv[2]));
    return(0);
} */
```
</details>

---

### ft_strcspn
```
Assignment name	: ft_strcspn
Expected files	: ft_strcspn.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the function strcspn
(man strcspn).

The function should be prototyped as follows:

size_t	ft_strcspn(const char *s, const char *reject);
```

<details>
  <summary>Answer ft_strcspn gitbook (indexes)</summary>
  
```c
// Needed for size_t
#include <stdio.h>

size_t ft_strcspn(const char *s, const char *reject)
{
    size_t i;
    size_t j;
    
    i = 0;
    // Looping over the whole string
    while(s[i++])
    {
        j = 0;
        // Check the current string char against every char in charset
        while (reject[j])
        {
            // If character found, return index in current string
            if (s[i] == reject[j++])
            	return (i);
        }
    }
    // If we spanned the whole string, return i, in that case the
    // rejected char found is the NULL-terminating one
    return (i);
}
```
</details>

<details>
  <summary>Answer ft_strcspn gitbook (pointers)</summary>
  
```c
#include <stdio.h>

size_t ft_strcspn(const char *s, const char *reject)
{
    // Save a pointer to the start of s
    const char *og = s;
    const char *s2;
    
    // Looping over the whole string 
    while (*s++)
    {
        // Set s2 to be the start of reject
        // that way we keep the reject pointer to its original position
        // Then loop over the whole charset
        s2 = reject;
        while (*s2)
        {
            // If current string charcter found in charset, return the
            // number of characters spanned
            if (*s == *s2++)
                // Here we make use of the original pointer to calculate
                // the number of char. spanned
                return (s - og);
        }
    }
    // Same as above, we use the original pointer to calculate the number
    // of character spanned
    return (s - og);
}
```
</details>

<details>
  <summary>Answer ft_strcspn pasqualerossi</summary>
  
```c
#include <stdio.h>

size_t  ft_strcspn(const char *s, const char *reject)
{
    int     i = 0;
    int     j = 0;

    while (s[i] != '\0')
    {
		j = 0;
        while (reject[j] != '\0')
        {
            if(s[i] == reject[j])
                return (i);
            j++;
        }
        i++;
    }
    return (i);
}
```
</details>

<details>
  <summary>Answer ft_strcspn emreakdik</summary>
  
```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>

size_t  ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (reject[k] != '\0')
		{
			if (reject[k] == s[i])
				return (i);
			k++;
		}
		k = 0;
		i++;
	}
	return (i);
}

/* int    ft_strcmp(char *s1, char *s2);
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc == 3)
        printf("ft_strcmp(\"%s\", \"%s\") = %d\n", argv[1], argv[2], ft_strcmp(argv[1], argv[2]));
    return(0);
} */
```
</details>

---

### ft_strdup
```
Assignment name  : ft_strdup
Expected files   : ft_strdup.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Reproduce the behavior of the function strdup (man strdup).

Your function must be declared as follows:

char    *ft_strdup(char *src);
```

<details>
  <summary>Answer ft_strdup gitbook</summary>
  
```c
#include <stdlib.h>

char    *ft_strdup(char *src)
{
	char	*tmp; //we will duplicate str into this variable
	int	len; 
	int	i;

	len = 0;
	i = 0;
	while (src[len]) //we calculate the length of src to create a place with enough memory
		len++;
	tmp = malloc(sizeof(char) * len + 1); //we allocate some space thanks to malloc. + 1 because the string need some space for the extra "\0" at the end (don't forget it !)
	if (!tmp) //malloc protection
		return (NULL);
	while (src[i]) //loop to complete the new string
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = 0; //adding the null character at the end
	return (tmp);
}


#include <stdio.h>

int main()
{
	char	*a;
	a = "Hello World";
	printf("%s\n", ft_strdup(a));
}
```
</details>

<details>
  <summary>Answer ft_strdup pasqualerossi</summary>
  
```c
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int	i = 0;
	int	length = 0;
	char	*strcpy;

	while (src[length])
		length++;
	strcpy = malloc(sizeof(*strcpy) * (length + 1));
	if (strcpy != NULL)
	{
		while (src[i])
		{
			strcpy[i] = src[i];
			i++;
		}
		strcpy[i] = '\0';
	}
	return (strcpy);
}
```
</details>

<details>
  <summary>Answer ft_strdup emreakdik</summary>
  
```c
#include <stdlib.h>
#include <stdio.h>

char    *ft_strdup(char *src)
{
	int	i;
	char *dest;

	i = 0;
	while (src[i] != '\0')
		i++;
	dest = malloc(sizeof (char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

/* char    *ft_strdup(char *src);
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        printf("ft_strdup(\"\") = %s\n", ft_strdup(""));
        return(0);
    }
    printf("ft_strdup(\"%s\") = %s\n", argv[1], ft_strdup(argv[1]));
    return(0);
} */
```
</details>

---

### ft_strpbrk
```
Assignment name	: ft_strpbrk
Expected files	: ft_strpbrk.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the function strpbrk
(man strpbrk).

The function should be prototyped as follows:

char	*ft_strpbrk(const char *s1, const char *s2);

---------------------------------------------------------------
STRPBRK(3) (simplified)

NAME
     strpbrk –- locate multiple characters in string
LIBRARY
     Standard C Library (libc, -lc)
SYNOPSIS
     #include <string.h>
     char *strpbrk(const char *s, const char *charset);

DESCRIPTION
     The strpbrk() function locates in the null-terminated string s the first
     occurrence of any character in the string charset and returns a pointer to this
     character.  If no characters from charset occur anywhere in s strpbrk()
     returns NULL.
RETURN VALUES
     The strpbrk() function return a pointer to the first occurence of any character
     in the string,if no characters occur anywhere in s, strpbrk() returns NULL.
```

<details>
  <summary>Answer ft_strpbrk gitbook</summary>
  
```c
char	*ft_strpbrk(const char *s1, const char *s2)
{
	int i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s2[j])
		{
			if (s2[j] == s1[i])
				return (s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
```
</details>

<details>
  <summary>Answer ft_strpbrk pasqualerossi</summary>
  
```c
#include <stdio.h>
#include <string.h>

char *ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;
	
	if (!s1 || !s2)
	{
		return (0);
	}
	while(*s1)
	{
		i = 0;
	   	while(s2[i])
		{
			if(*s1 == s2[i])
				return (char *) s1;
			i++;
		}
		s1++;	
	}
	return (0);
}
```
</details>

---

### ft_strrev
```
Assignment name  : ft_strrev
Expected files   : ft_strrev.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that reverses (in-place) a string.

It must return its parameter.

Your function must be declared as follows:

char    *ft_strrev(char *str);
```

<details>
  <summary>Answer ft_strrev gitbook</summary>
  
```c
#include <stdio.h>

char    *ft_strrev(char *str)
{
	int i;
	int len;
	char tmp;


	i = 0;
	len = 0;
	while (str[len])
		len++;
	while (i < len - 1)
	{
		tmp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = tmp;
		i++;
		len--;
	}
	return (str);
}

/*int	main(void)
{
	char s[] = "Hello World";
	ft_strrev(s);
	printf("%s\n", s);
	return (0);
}
```
</details>

<details>
  <summary>Answer ft_strrev pasqualerossi</summary>
  
```c
char *ft_strrev(char *str)
{
	int i = -1;
	int length = 0;
	char temporary;

	while (str[length])
		length++;
	while (++i < length / 2)
	{
		temporary = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temporary;
	}
	return (str);
}
```
</details>

<details>
  <summary>Answer ft_strrev emreakdik</summary>
  
```c
char *ft_strrev(char *str)
{
	int i = -1;
	int length = 0;
	char temporary;

	while (str[length])
		length++;
	while (++i < length / 2)
	{
		temporary = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temporary;
	}
	return (str);
}

/* #include <stdio.h>

char *ft_strrev(char *str);

int main(int argc, char **argv)
{
    if (argc == 2)
        printf("%s", ft_strrev(argv[1]));
    return (0);
} */
```
</details>

---

### ft_strspn
```
Assignment name	: ft_strspn
Expected files	: ft_strspn.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the strspn function 
(man strspn).

The function should be prototyped as follows:

size_t	ft_strspn(const char *s, const char *accept);
```

<details>
  <summary>Answer ft_strspn gitbook</summary>
  
```c
#include <stdlib.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	int i;
	int	j;
	int check;

	i = 0;
	while (s[i])
	{
		j = 0;
		check = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				check = 1;
			j++;
		}
		if (check == 0)
			return (i);
		i++;
	}
	return (i);
}

/*#include <stdio.h>
int main()
{
	char *s = "hello";
	const char *accept = "jfkhpell";
	printf("%zu\n", ft_strspn(s, accept));
}*/
```
</details>

<details>
  <summary>Answer ft_strspn pasqualerossi</summary>
  
```c
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	return (0);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t i = 0;

	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break;
		++i;
	}
	return (i);
}
```
</details>

---

### inter
```
Assignment name  : inter
Expected files   : inter.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and displays, without doubles, the
characters that appear in both strings, in the order they appear in the first
one.

The display will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Examples:

$>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
$>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
$>./inter "rien" "cette phrase ne cache rien" | cat -e
rien$
$>./inter | cat -e
$
```

<details>
  <summary>Answer inter gitbook</summary>
  
```c
#include <unistd.h>

int	ft_putchar(char c);

int	main(int ac, char **av)
{
	int	i = 0, j;
	// create an array of int that will act as a lookup table
	// 256 is because of the ascii table, each one will
	// correspond to a single character
	int	lookup[256] = {};

	if (ac == 3)
	{
		// looping over the whole string
		while (av[1][i])
		{
			j = 0;
			// comparing against every character in the
			// second string
			while (av[2][j])
			{
				// checking if characters are the same
				// as well as checking in the lookup
				// table if the character not already
				// found
				if (av[1][i] == av[2][j] && !lookup[(int)av[2][j]])
				{
					// marking the character found
					// in the lookup table
					lookup[(int)av[2][j]] = 1;
					// writing the character
					// to the screen
					ft_putchar(av[2][j]);
				}
				j++;
			}
			i++;
		}
	}
	ft_putchar('\n');
}

int	ft_putchar(char c)
{
	return write(1, &c, 1);
}
```
</details>

<details>
  <summary>Answer inter pasqualerossi</summary>
  
```c
#include <unistd.h>

int	iter(char *str, char c, int len)
{
	int	i = 0;

	while (str[i] && (i < len || len == -1))
		if (str[i++] == c)
			return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	i;

	if (argc == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			if (!iter(argv[1], argv[1][i], i) && iter(argv[2], argv[1][i], -1))
				write(1, &argv[1][i], 1);
			i += 1;
		}
	}
	write(1, "\n", 1);
	return (0);
}
```
</details>

<details>
  <summary>Answer inter emreakdik</summary>
  
```c

#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;
	int k;
	int l;
	char *s1;
	char *s2;

	i = 0;
	l = 0;
	if (ac == 3)
	{
		s1 = av[1];
		s2 = av[2];
		while (s1[i] != '\0')
		{
			k = 0;
			while (s2[k] != '\0')
			{
				if(s1[i] == s2[k])
				{ 
					l = 0;
					while (s1[l] != s1[i])
						l++;
					if (l == i)
					{
						l = 0;
						while (s2[l] != s2[k])
							l++;
						if (l == k)
							write(1, &s1[i], 1);
					}
				}
				k++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
}
```
</details>

---

### is_power_of_2
```
Assignment name  : is_power_of_2
Expected files   : is_power_of_2.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that determines if a given number is a power of 2.

This function returns 1 if the given number is a power of 2, otherwise it returns 0.

Your function must be declared as follows:

int	    is_power_of_2(unsigned int n);
```

<details>
  <summary>Answer is_power_of_2 gitbook</summary>
  
```c
int	    is_power_of_2(unsigned int n)
{

// we will initialize a test variable to 1, and we will multiply it by 2 until it is equal to or greater than the variable we have been given as a parameter (n). If the two variables are equal it means that it is a power of 2 (since we have always multiplied this number by 2)
	
	int test = 1;

	while (test <= n)
	{
		if (test == n)
			return  (1); // test is a power of 2
		test = test * 2;
	}
	// we will leave the loop if the test variable is greater than n. this means that it is not a power of 2 an we need to return 0.
	return (0);
}


#include <stdio.h>
int main()
{
	printf("%d", is_power_of_2(16));
}
```
</details>

<details>
  <summary>Answer is_power_of_2 pasqualerossi</summary>
  
```c
int is_power_of_2(unsigned int n)
{
	if (n == 0)
		return (0);
	while (n % 2 == 0)
		n /= 2;
	return ((n == 1) ? 1 : 0);
}
```
</details>

<details>
  <summary>Answer is_power_of_2 emreakdik</summary>
  
```c
#include <stdio.h>

int         is_power_of_2(unsigned int n)
{
	if (n == 0)
		return (0);
	while (n > 1)
	{
		if (n % 2 == 0)
			n = n / 2;
		else
			return (0);
	}
	return (1);
}

/* int	    is_power_of_2(unsigned int n);
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc == 1)
        return(0);
    printf("is_power_of_2(\"%s\") = %d\n", argv[1], is_power_of_2(atoi(argv[1])));
    return(0);
} */
```
</details>

---

### last_word
```
Assignment name  : last_word
Expected files   : last_word.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays its last word followed by a \n.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or there are no words, display a newline.

Example:

$> ./last_word "FOR PONY" | cat -e
PONY$
$> ./last_word "this        ...       is sparta, then again, maybe    not" | cat -e
not$
$> ./last_word "   " | cat -e
$
$> ./last_word "a" "b" | cat -e
$
$> ./last_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
$>
```

<details>
  <summary>Answer last_word gitbook</summary>
  
```c
#include <unistd.h>

int main (int ac, char **a)
{
	if (ac == 2)
	{
		int i = 0;

		// getting to the end of the string
		while (a[1][i])
			i++;
		i--;
		// looping over the whole string backwards
		// until we found a space
		while (a[1][i] > 32)
			i--;
		i++;
		// getting back to the end and writing the last word to
		// the screen
		while (a[1][i])
		{
			write(1, &a[1][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
}
```
</details>

<details>
  <summary>Answer last_word pasqualerossi</summary>
  
```c
#include <unistd.h>

void	last_word(char *str)
{
	int	j = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] >= 33 && str[i + 1] <= 126)
			j = i + 1;
		i++;
	}
	while (str[j] >= 33 && str[j] <= 127)
	{
		write(1, &str[j], 1);
		j++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		last_word(argv[1]);
	write(1, "\n", 1);
	return (0);
}
```
</details>

<details>
  <summary>Answer last_word emreakdik</summary>
  
```c
#include <unistd.h>

void	last_word(char *str)
{
	int	j = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] >= 33 && str[i + 1] <= 126)
			j = i + 1;
		i++;
	}
	while (str[j] >= 33 && str[j] <= 127)
	{
		write(1, &str[j], 1);
		j++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		last_word(argv[1]);
	write(1, "\n", 1);
	return (0);
}
```
</details>

---

### max
```
Assignment name  : max
Expected files   : max.c
Allowed functions:
--------------------------------------------------------------------------------

Write the following function:

int		max(int* tab, unsigned int len);

The first parameter is an array of int, the second is the number of elements in
the array.

The function returns the largest number found in the array.

If the array is empty, the function returns 0.
```

<details>
  <summary>Answer max gitbook</summary>
  
```c
int		max(int* tab, unsigned int len)
{
	int count = 0;
	int result = 0;
	int i = 0;
	if (len > 0)
	{
		while (count < len)
		{
			if (tab[i] > result)
				result = tab[i];
			i++;
			count++;
		}
		return (result);
	}
	return (0);
}

#include <stdio.h>

int main()
{
	int int_tab[] = {1, 3, 2, 10, 9};
	printf("%d", max(int_tab, 5));
}
```
</details>

<details>
  <summary>Answer max pasqualerossi</summary>
  
```c
int max(int *tab, unsigned int len)
{
	if (len == 0)
		return (0);
	
	unsigned int result;
	unsigned int i = 0;
	
	result = tab[i];
	while(i < len)
	{
		if (result <  tab[i])
		{
			result = tab[i];
		}
		i++;
	}
	return result;
}
```
</details>

<details>
  <summary>Answer max emreakdik</summary>
  
```c
int	max(int* tab, unsigned int len)
{
	if (len == 0)
		return (0);
	int res = tab[0];
	for (unsigned int i = 0; i < len; i += 1)
	{
		if (res < tab[i])
			res = tab[i];
	}
	return (res);
}

/* int		max(int* tab, unsigned int len);
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 3)
        return(0);
    int *tab = malloc(sizeof(int) * (argc - 1));
    
    printf("max( {");
    for (int i = 2; i < argc; i++)
    {
        printf("%s", argv[i]);
        if (i != argc - 1)
            printf(";");
        tab[i - 2] = atoi(argv[i]);
    }
    printf("} , %s) = %d\n", argv[1], max(tab, atoi(argv[1])));
    // printf("max(\"%s\") = %d\n", argv[1], is_power_of_2(atoi(argv[1])));
    return(0);
} */
```
</details>

---

### print_bits
```
Assignment name  : print_bits
Expected files   : print_bits.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a function that takes a byte, and prints it in binary WITHOUT A NEWLINE
AT THE END.

Your function must be declared as follows:

void	print_bits(unsigned char octet);

Example, if you pass 2 to print_bits, it will print "00000010"
```

<details>
  <summary>Answer print_bits gitbook</summary>
  
```c
#include <unistd.h>

void print_bits(unsigned char octet)
{
    int i = 8; // Initialize a counter variable i to 8
    unsigned char bit = 0; // Initialize a variable bit to 0

    while (i--) // Loop through each bit of octet
    {
        bit = (octet >> i & 1) + 48; // Shift the bit of octet to the right i times and use the bitwise AND operator with 1 to get the bit value. Then add 48 to convert the bit value to its ASCII representation ('0' or '1')
        write (1, &bit, 1); // Write the ASCII representation of the bit to the standard output (stdout)
    }
}


/* if you want to test your code : */
int main()
{
	unsigned char octet = 3;
	print_bits(octet);
}

```
</details>

<details>
  <summary>Answer print_bits pasqualerossi</summary>
  
```c
#include <unistd.h>

void print_bits(unsigned char octet)
{
	int	i = 8;
	unsigned char 	bit;

	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}
```
</details>

<details>
  <summary>Answer print_bits emreakdik</summary>
  
```c
#include <unistd.h>

void print_bits(unsigned char octet)
{
	int	i = 8;
	unsigned char 	bit;

	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}

/* #include <unistd.h>
void print_bits(unsigned char octet);

int main(int ac, char **av)
{
    if (ac == 2)
        print_bits(av[1][0]);
    write(1, "\n", 1);
    return (0);
} */
```
</details>

---

### reverse_bits
```
Assignment name  : reverse_bits
Expected files   : reverse_bits.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that takes a byte, reverses it, bit by bit (like the
example) and returns the result.

Your function must be declared as follows:

unsigned char	reverse_bits(unsigned char octet);

Example:

  1 byte
_____________
 0010  0110
     ||
     \/
 0110  0100
```

<details>
  <summary>Answer reverse_bits gitbook</summary>
  
```c
unsigned char	reverse_bits(unsigned char octet)
{
	unsigned int	i;
	unsigned char	res = 0;

	i = 8;
	while (i--)
	{
		// shift all the bits of res by 1 to the left
		// i.e. res: 0000 0101 => 0000 1010
		// perform a bitwise AND on LSB of octet AND 1
		// Least Significant Bit is the right most one
		// i.e octet: 0000 0101 => 1
		// it then performs a bitwise OR between the 
		// two LSB and stores the result in res
		// 0000 1010 | 0000 0001 => res: 0000 1011
		res = (res << 1) | (octet & 1);
		// shifting the original octet by 1 to the right
		// so that in next iteration we have the next bit
		octet = octet >> 1;
	}
	return (res);
}

// If you want to test the code:
int	main(void)
{
	unsigned char bit = 0;
	// by changing the number on the next line, you change
	// the bits that are sent to the reverse_bits function
	// 5 => 0000 0101, the result should be 1010 0000
	unsigned char res = reverse_bits((unsigned char)5);

	int i = 8;
	while (i--)
	{
		bit = (res >> i & 1) + 48;
		printf("%c", bit);
	}
}
```
</details>

<details>
  <summary>Answer reverse_bits pasqualerossi</summary>
  
```c
unsigned char	reverse_bits(unsigned char octet)
{
	int		i = 8;
	unsigned char	res = 0;

	while (i > 0)
	{
		res = res * 2 + (octet % 2);
		octet = octet / 2;
		i--;
	}
	return (res);
}
```
</details>

<details>
  <summary>Answer reverse_bits emreakdik</summary>
  
```c
unsigned char	reverse_bits(unsigned char octet)
{
	int		i = 8;
	unsigned char	res = 0;

	while (i > 0)
	{
		res = res * 2 + (octet % 2);
		octet = octet / 2;
		i--;
	}
	return (res);
}

/* #include <stdio.h>

unsigned char	reverse_bits(unsigned char octet);

int main(int ac, char **av)
{
    if (ac == 2)
        printf("%d", reverse_bits(av[1][0]));
    return (0);
} */
```
</details>

---

### snake_to_camel
```
Assignment name  : snake_to_camel
Expected files   : snake_to_camel.c
Allowed functions: malloc, free, realloc, write
--------------------------------------------------------------------------------

Write a program that takes a single string in snake_case format
and converts it into a string in lowerCamelCase format.

A snake_case string is a string where each word is in lower case, separated by
an underscore "_".

A lowerCamelCase string is a string where each word begins with a capital letter
except for the first one.

Examples:
$>./camel_to_snake "here_is_a_snake_case_word"
hereIsASnakeCaseWord
$>./camel_to_snake "hello_world" | cat -e
helloWorld$
$>./camel_to_snake | cat -e
$
```

<details>
  <summary>Answer snake_to_camel gitbook</summary>
  
```c
#include <unistd.h>

int toUpper(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}

int ft_putchar(char c)
{
    return write(1, &c, 1);
}

int main(int ac, char **av)
{
    int i;
    
    // do things only if there is only one argument
    if (ac == 2)
    {
        i = 0;
        // looping over the whole string
        while (av[1][i])
        {
            // If we encounter a _, we have to make the
            // next letter uppercase and not print the _
            // so we only print the uppercase letter
            if (av[1][i] == '_')
                // here we use the ++i operator to
                // increment i before accessing the value
                // that way we skip the _
                ft_putchar(toUpper(av[1][++i]));
            else
                // in all other cases, we simply write
                // the character to the screen
                ft_putchar(av[1][i]);
            i++;
        }
    }
    // and finally, we have our newline
    // putting it here makes us only need one in all the 
    // cases 
    ft_putchar('\n');
}(0)
}
```
</details>

<details>
  <summary>Answer snake_to_camel pasqualerossi</summary>
  
```c
#include <unistd.h>

int main(int argc, char **argv)
{
	int i = 0;
	
	if (argc ==2 )
	{
		while(argv[1][i] != '\0')
		{
			if (argv[1][i] == '_')
			{
				i++;
				argv[1][i] = argv[1][i]-32;
			}
			write (1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
```
</details>

<details>
  <summary>Answer snake_to_camel emreakdik</summary>
  
```c
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		for (int i = 0; argv[1][i]; i += 1)
		{
			if (argv[1][i] == '_')
			{
				i += 1;
				argv[1][i] -= 32;
			}
			write(STDOUT_FILENO, &argv[1][i], 1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	return EXIT_SUCCESS;
}
```
</details>

---

### swap_bits
```
Assignment name  : swap_bits
Expected files   : swap_bits.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that takes a byte, swaps its halves (like the example) and
returns the result.

Your function must be declared as follows:

unsigned char	swap_bits(unsigned char octet);

Example:

  1 byte
_____________
 0100 | 0001
     \ /
     / \
 0001 | 0100
```

<details>
  <summary>Answer swap_bits gitbook</summary>
  
```c
// Function to swap the four most significant bits (left four bits) with the four least significant bits (right four bits) of an 8-bit octet
unsigned char swap_bits(unsigned char octet)
{
    // Shift the four most significant bits to the right to the position of the four least significant bits, and OR them with the four least significant bits shifted to the left to the position of the four most significant bits
    return ((octet >> 4 | octet << 4));
}

```
</details>

<details>
  <summary>Answer swap_bits pasqualerossi</summary>
  
```c
unsigned char swap_bits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}
```
</details>

<details>
  <summary>Answer swap_bits emreakdik</summary>
  
```c
#include <unistd.h>

unsigned char	swap_bits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}

/* #include <unistd.h>

unsigned char	swap_bits(unsigned char octet);

int	main(int argc, char **argv)
{
	unsigned char c;
	(void)argc;

	c = argv[1][0];
	write(1, &c, 1);
	write(1, "\n", 1);
	c = swap_bits(c);
	write(1, &c, 1);
	write(1, "\n", 1);
	return (0);
} */
```
</details>

---

### union
```
Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Example:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>
```

<details>
  <summary>Answer union gitbook</summary>
  
```c
#include <unistd.h>

int main(int ac, char **av)
{
    // create a lookup table for all chars in ascii table
    int i = 0, lookup[256 = {0};
    
    if (ac == 3)
    {
        // loop over the whole first string
        // for each character, switch the value in
        // the lookup table
        while(av[1][i])
        	lookup[(int)av[1][i++]] = 1;
        i = 0;
        // do the same thing for the second string
        while(av[2][i])
        	lookup[(int)av[2][i++]] = 1;
        i = 0;
        
        // loop over the first string to write the
        // seen chars to the screen, switch back the
        // value in the lookup table once printed
        while (av[1][i])
        {
            if (lookup[(int)av[1][i]])
            {
                write(1, &av[1][i], 1);
                lookup[(int)av[1][i]] = 0;
            }
            i++;
        }
        i = 0;
        while (av[2][i])
        {
            if (lookup[(int)av[2][i]])
            {
                write(1, &av[2][i], 1);
                lookup[(int)av[2][i]] = 0;
            }
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}
```
</details>

<details>
  <summary>Answer union pasqualerossi</summary>
  
```c
#include <unistd.h>

int check(int c, char *str, int index)
{
	int i = 0;
	
	while(i < index)
	{
		if (str[i] == c)
			return 0;
		i++;
	}
	return  1;
}

int main(int argc, char **argv)
{	
	int i = 0;
	int j = 0;
	int k = 0;
	
	if (argc == 3)
	{
		while(argv[1][i] != '\0')
		{
			i++;
		}
		while(argv[2][j] != '\0')
		{
			argv[1][i] = argv[2][j];
			i++;
			j++;
		}
		i--;
		while(k <= i)
		{
			if(check(argv[1][k], argv[1], k) == 1) 
				write (1, &argv[1][k], 1); 
			k++;
		}
	}
	write (1, "\n", 1);
}
```
</details>

<details>
  <summary>Answer union emreakdik</summary>
  
```c
#include <unistd.h>

int check(int c, char *str, int index)
{
	int i = 0;
	
	while(i < index)
	{
		if (str[i] == c)
			return 0;
		i++;
	}
	return  1;
}

/* int main(int argc, char **argv)
{	
	int i = 0;
	int j = 0;
	int k = 0;
	
	if (argc == 3)
	{
		while(argv[1][i] != '\0')
		{
			i++;
		}
		while(argv[2][j] != '\0')
		{
			argv[1][i] = argv[2][j];
			i++;
			j++;
		}
		i--;
		while(k <= i)
		{
			if(check(argv[1][k], argv[1], k) == 1) 
				write (1, &argv[1][k], 1); 
			k++;
		}
	}
	write (1, "\n", 1);
} */
```
</details>

---

### wdmatch
```
Assignment name  : wdmatch
Expected files   : wdmatch.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and checks whether it's possible to
write the first string with characters from the second string, while respecting
the order in which these characters appear in the second string.

If it's possible, the program displays the string, followed by a \n, otherwise
it simply displays a \n.

If the number of arguments is not 2, the program displays a \n.

Examples:

$>./wdmatch "faya" "fgvvfdxcacpolhyghbreda" | cat -e
faya$
$>./wdmatch "faya" "fgvvfdxcacpolhyghbred" | cat -e
$
$>./wdmatch "quarante deux" "qfqfsudf arzgsayns tsregfdgs sjytdekuoixq " | cat -e
quarante deux$
$>./wdmatch "error" rrerrrfiiljdfxjyuifrrvcoojh | cat -e
$
$>./wdmatch | cat -e
$
```

<details>
  <summary>Answer wdmatch gitbook</summary>
  
```c
#include <unistd.h>

int main(int ac, char **av)
{
    if (ac == 3)
    {
        const char *s1 = av[1];
        const char *s2 = av[2];
        int len = 0, i = 0;
        
        while (s1[len])
            len++;
        
        // checking all characters of s1 in s2
        while (i < len && *s2)
        {
            // next line checks if current s1 char is
            // equal to s2 char, after the comparison is
            // done, we increment the s2 pointer
            // even if the condition doesn't match
            // if the condition match, we increment i to
            // check for next s1 char
            if (s1[i] == *s2++)
                i++;
        }
        if (i == len)
            write(1, s1, len);
    }
    write(1, "\n", 1);
    return (0);
}
```
</details>

<details>
  <summary>Answer wdmatch pasqualerossi</summary>
  
```c
#include <unistd.h>

void ft_putstr(char const *str)
{
	int i = 0;

	while (str[i])
		write(1, &str[i++], 1);
}

int	main(int argc, char const *argv[])
{
	int i = 0;
	int j = 0;

	if (argc == 3)
	{
		while (argv[2][j])
			if (argv[2][j++] == argv[1][i])
				i += 1;
		if (!argv[1][i])
			ft_putstr(argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}
```
</details>

<details>
  <summary>Answer wdmatch emreakdik</summary>
  
```c
#include <unistd.h>

void ft_putstr(char const *str)
{
	int i = 0;

	while (str[i])
		write(1, &str[i++], 1);
}

int	main(int argc, char const *argv[])
{
	int i = 0;
	int j = 0;

	if (argc == 3)
	{
		while (argv[2][j])
			if (argv[2][j++] == argv[1][i])
				i += 1;
		if (!argv[1][i])
			ft_putstr(argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}
```
</details>

---
---
## Lvl 3

### template
```
template
```

<details>
  <summary>Answer template</summary>
  
```c
#include <unistd.h>

int main (int argc, char **argv)
{
	return(0)
}
```
</details>

---


---
---
## Lvl 4

### template
```
template
```

<details>
  <summary>Answer template</summary>
  
```c
#include <unistd.h>

int main (int argc, char **argv)
{
	return(0)
}
```
</details>

---