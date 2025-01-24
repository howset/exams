/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations_tester.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nryser <nryser@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 02:37:08 by nryser            #+#    #+#             */
/*   Updated: 2025/01/09 02:41:22 by nryser           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

// Function to generate all permutations (used in tester for expected results)
void generate_permutations(char *str, char *current, int *used, int depth, int len, char **results, int *result_count, int max_results)
{
	if (*result_count >= max_results) // Prevent buffer overflow
		return;

	if (depth == len)
	{
		results[*result_count] = strdup(current);
		(*result_count)++;
		return;
	}
	for (int i = 0; i < len; i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			current[depth] = str[i];
			generate_permutations(str, current, used, depth + 1, len, results, result_count, max_results);
			used[i] = 0;
		}
	}
}

// Sort the array of strings alphabetically
int compare_strings(const void *a, const void *b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}

// Tester function
int test_permutations(const char *program, char *input)
{
	char command[256];
	snprintf(command, sizeof(command), "%s %s", program, input);

	FILE *fp = popen(command, "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to execute %s\n", program);
		return 1;
	}

	// Read program output
	int max_results = 1000000; // Maximum number of permutations to handle
	char **output = malloc(max_results * sizeof(char *));
	int output_count = 0;
	char line[1024];

	while (fgets(line, sizeof(line), fp))
	{
		line[strcspn(line, "\n")] = '\0'; // Remove newline
		output[output_count++] = strdup(line);
	}
	pclose(fp);

	// Generate expected results
	int len = ft_strlen(input);
	char *current = malloc(len + 1);
	current[len] = '\0';
	int *used = calloc(len, sizeof(int));
	char **expected = malloc(max_results * sizeof(char *));
	int expected_count = 0;

	generate_permutations(input, current, used, 0, len, expected, &expected_count, max_results);

	// Sort expected results
	qsort(expected, expected_count, sizeof(char *), compare_strings);

	// Check for correctness
	int success = 1;
	if (expected_count != output_count)
	{
		fprintf(stderr, "Mismatch in number of permutations (expected %d, got %d)\n", expected_count, output_count);
		success = 0;
	}
	else
	{
		for (int i = 0; i < expected_count; i++)
		{
			if (strcmp(expected[i], output[i]) != 0)
			{
				fprintf(stderr, "Mismatch at line %d: expected '%s', got '%s'\n", i + 1, expected[i], output[i]);
				success = 0;
				break;
			}
		}
	}

	// Free memory
	for (int i = 0; i < output_count; i++)
		free(output[i]);
	free(output);

	for (int i = 0; i < expected_count; i++)
		free(expected[i]);
	free(expected);

	free(current);
	free(used);

	if (success)
		printf("Test passed for input '%s'\n", input);
	else
		printf("Test failed for input '%s'\n", input);

	return !success;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <program> [test strings...]\n", argv[0]);
		return 1;
	}

	const char *program = argv[1];
	int failed_tests = 0;

	for (int i = 2; i < argc; i++)
	{
		if (test_permutations(program, argv[i]))
			failed_tests++;
	}

	if (failed_tests == 0)
		printf("All tests passed!\n");
	else
		printf("%d test(s) failed.\n", failed_tests);

	return failed_tests;
}

//gcc -o tester permutations_tester.c
//./tester ./a.out a ab abc abcd
