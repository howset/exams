/* #include "argo.h"

int		peek(FILE *stream);
void	unexpected(FILE *stream);
int		accept(FILE *stream, char c);
int		expect(FILE *stream, char c);

int		argo(json *dst, FILE *stream);
json	parse_json(FILE *stream);
json	parse_string_json(FILE *stream);
json	parse_map(FILE *stream);
json	parse_number(FILE *stream);
char	*parse_string(FILE *stream);
void	set_g_error(void);

int		g_error = 0;
int		g_error_no_key = 0;

int	argo(json *dst, FILE *stream)
{
	if (!stream)
		return (-1);

	*dst = parse_json(stream);
	if (g_error_no_key)
	{
		return (-1);
	}
	if (g_error)
	{
		unexpected(stream);
		return (-1);
	}
	return (1);
}

json	parse_json(FILE *stream)
{
	json	nothing;

	if (peek(stream) == '-' || isdigit(peek(stream)))
		return (parse_number(stream));
	else if (peek(stream) == '"')
		return (parse_string_json(stream));
	else if (peek(stream) == '{')
		return (parse_map(stream));
	else
	{
		nothing.type = STRING;
		nothing.string = NULL;
		g_error = 1;
		return (nothing);
	}
}

json	parse_number(FILE *stream)
{
	json	num_json;
	int		res;
	int		ret_fscanf;

	num_json.type = INTEGER;
	num_json.integer = -42;
	ret_fscanf = fscanf(stream, "%d", &res);
	if (ret_fscanf <= 0 || ret_fscanf == EOF)
	{
		set_g_error();
		return (num_json);
	}
	num_json.integer = res;
	return (num_json);
}

json	parse_string_json(FILE *stream)
{
	json	json_string;

	json_string.type = STRING;
	json_string.string = parse_string(stream);
	return (json_string);
}

char	*parse_string(FILE *stream)
{
	char	*res;
	char	cur_char;
	int		str_len;

	res = malloc(sizeof(char));
	res[0] = '\0';
	str_len = 0;
	if (!accept(stream, '"'))
	{
		set_g_error();
		return (res);
	}
	while (peek(stream) != '"' && peek(stream) != EOF && !g_error)
	{
		str_len++;
		res = realloc(res, (str_len + 1) * sizeof(char));
		res[str_len] = '\0';
		cur_char = getc(stream);
		if (cur_char == '\\')
		{
			if (peek(stream) != '\\' && peek(stream) != '\"')
			{
				set_g_error();
				return (res);
			}
			cur_char = getc(stream);
		}
		res[str_len - 1] = cur_char;
	}
	if (!accept(stream, '"'))
	{
		set_g_error();
	}
	return (res);
}

json	parse_map(FILE *stream)
{
	json	json_map;

	json_map.type = MAP;
	json_map.map.data = NULL;
	json_map.map.size = 0;
	if (!accept(stream, '{'))
	{
		set_g_error();
		return (json_map);
	}
	if (peek(stream) != EOF && peek(stream) != EOF)
	{
		do
		{
			pair new_pair;
			if (peek(stream) != '"')
			{
				g_error_no_key = 1;
				return (json_map);
			}
			new_pair.key = parse_string(stream);
			if (g_error)
			{
				//printf("HEREH\n");
				free(new_pair.key);
				return (json_map);
			}
			if (!accept(stream, ':'))
			{
				set_g_error();
				return (json_map);
			}
			new_pair.value = parse_json(stream);
			if (g_error)
			{
				free(new_pair.key);
				free_json(new_pair.value);
				return (json_map);
			}
			json_map.map.size++;
			json_map.map.data = realloc(json_map.map.data, json_map.map.size
					* sizeof(pair));
			json_map.map.data[json_map.map.size - 1] = new_pair;
		} while (accept(stream, ','));
	}
	if (g_error || !accept(stream, '}'))
	{
		set_g_error();
		return (json_map);
	}
	return (json_map);
}

void	set_g_error(void)
{
	//printf("g_error_set\n");
	g_error = 1;
}

int	peek(FILE *stream)
{
	int	c;

	c = getc(stream);
	ungetc(c, stream);
	return (c);
}

void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("Unexpected token '%c'\n", peek(stream));
	else
		printf("Unexpected end of input\n");
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return (1);
	}
	return (0);
}

int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
	{
		return (1);
	}
	unexpected(stream);
	return (0);
}
 */

 #include "argo.h"

 int	peek(FILE *stream)
 {
	 int	c = getc(stream);
	 ungetc(c, stream);
	 return c;
 }
 
 void	unexpected(FILE *stream)
 {
	 if (peek(stream) != EOF)
		 printf("unexpected token '%c'\n", peek(stream));
	 else
		 printf("unexpected end of input\n");
 }
 
 int	accept(FILE *stream, char c)
 {
	 if (peek(stream) == c)
	 {
		 (void)getc(stream);
		 return 1;
	 }
	 return 0;
 }
 
 int	expect(FILE *stream, char c)
 {
	 if (accept(stream, c))
		 return 1;
	 unexpected(stream);
	 return 0;
 }
 
 char	accept_and_get_next_scout(FILE *stream, char scout)
 {
	 accept(stream, scout);
	 return (peek(stream));
 }
 
 void	pace_whitespaces(FILE *stream, char *scout)
 {
	 *scout = peek(stream);
	 while (*scout == ' ')
	 {
		 accept(stream, *scout);
		 *scout = peek(stream);
	 }
 }
 
 // opening \" has already been swallowed
 char	*extract_string(FILE *stream)
 {
	 char	*str = NULL;
	 char	scout;
	 int	i = -1;
		
	 str = calloc(4096, sizeof(char));
	 if (!str)
		 return NULL;
	 scout = peek(stream);
	 while (scout != '\"' && scout != EOF)
	 {
		 if (scout == '\\')
		 {
			 accept(stream, scout);
			 scout = peek(stream);
			 if (scout == '\"')
				 str[++i] = '\"';
			 else
			 {
				 str[++i] = '\\';
				 str[++i] = scout;
			 }
		 }
		 else
			 str[++i] = scout;
		 accept(stream, scout);
		 scout = peek(stream);
	 }
	 if (expect(stream, '\"'))  // will print 'unexpected end of input'
		 return str;
	 free(str); // if EOF, then no closing \", report
	 return NULL;
 }
 
 int	parser(json *dst, FILE *stream)
 {
	 char	scout = 0;
	 char	*str = NULL;
	 int	num = 0;
 
	 dst->map.size = 0;
	 dst->map.data = NULL;
	 pace_whitespaces(stream, &scout);
	 if (scout == EOF) // this is only reached by ''
		 return -1;
	 if (isdigit(scout) || scout == '-' || scout == '+')
	 {
		 fscanf(stream, "%d", &num);
		 if ((scout != '0' && num == 0) || num == EOF)
			 return -1;
		 *dst = (json){.type = INTEGER, .integer = num};
		 return 1;
	 }
	 else if (scout == '\"')
	 {
		 accept(stream, scout);
		 str = extract_string(stream);
		 if (!str)
			 return -1;
		 *dst = (json){.type = STRING, .string = str};
		 return 1;
	 }
	 else if (scout == '{')
	 {
		 accept(stream, scout);
		 while (1)
		 {
			 dst->map.data = realloc(dst->map.data, \
					 (dst->map.size + 1) * sizeof(pair));
			 if (!dst->map.data)
				 return -1;
			 pace_whitespaces(stream, &scout);
			 if (!expect(stream, '\"'))
				 return -1;
			 str = extract_string(stream);
			 if (!str)
				 return -1;
			 dst->map.data[dst->map.size].key = str;
				 
			 pace_whitespaces(stream, &scout);
			 if (!expect(stream, ':'))
				 return -1;
			 pace_whitespaces(stream, &scout);
			 
			 if (parser(&dst->map.data[dst->map.size].value, stream) == -1)
				 return -1; // Error in recursive call
			 dst->map.size++;
 
			 // after parser() success, we only accept ',' or '}'
			 pace_whitespaces(stream, &scout);
			 if (scout == ',')
			 {
				 scout = accept_and_get_next_scout(stream, scout);
				 pace_whitespaces(stream, &scout);
				 continue ;
			 }
			 if (!expect(stream, '}'))
				 return -1;
			 return 1;
		 }
	 }
	 return (0);
 }
 
 int	argo(json *dst, FILE *stream)
 {
	 char	scout;
 
	 if (parser(dst, stream) == -1)
		 return -1;
	 pace_whitespaces(stream, &scout);
	 if (!expect(stream, EOF))
		 return -1;
	 return 1;
 }
 