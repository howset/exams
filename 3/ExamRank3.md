#### `ft_printf`
`ft_printf` is used to print formatted output to the screen. It contains the relevant header files (`<unistd.h>` and `<stdarg.h>`) and uses a variable argument list.

- `void ft_putstr(char *str, int *len)`: It is a helper function to print a string to the screen. If the string is NULL, it prints the string "(null)".

- `void ft_int(long long int nb, int *len, int base)`: It is an auxiliary function to print an integer to the screen according to the specified number base. It also handles negative numbers and adds a minus sign if necessary.

- `int ft_printf(const char *format, ...)`: This is the main function that prints formatted outputs to the screen. The `format` string specifies the format of the output. It recognizes special identifiers starting with the '%' sign and prints the relevant values ​​based on these identifiers. Supported tokens include `%s` (string), `%d` (decimal integer), `%x` (hexadecimal integer).

#### `get_next_line`
`get_next_line` performs the operation of reading from a file line by line. Contains the header file (`"get_next_line.h"`).

- `int ft_strlen(char *str)`: It is a helper function to calculate the length of a string.

- `char *ft_strjoin(char *str1, char *str2)`: It is a helper function to join two strings.

- `char *ft_substr(char *str, int i)`: It is a helper function to copy characters in a certain range.

- `int check(char *line)`: Checks for a newline character (line break) in the given string. Returns its index, if it exists; otherwise, it returns -1.

- `char *next_line(char *line, int fd)`: It is an auxiliary function that performs the operation of reading a line from the file. It reads up to `BUFFER_SIZE` and adds the read data to the string.

- `char *get_next_line(int fd)`: This is the main function that performs line by line reading from a file. It reads and returns lines from the file using the `check` and `next_line` functions. This function operates on a static variable `line` and stores the lines read from the file. When the read operation is completed, it performs the remaining data and memory cleaning operations.