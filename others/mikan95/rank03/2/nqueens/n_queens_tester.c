/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nryser <nryser@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 02:28:56 by nryser            #+#    #+#             */
/*   Updated: 2025/01/09 02:31:28 by nryser           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to validate a single solution
int is_valid_solution(int *solution, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			// Check for conflicts in rows or diagonals
			if (solution[i] == solution[j] || abs(solution[i] - solution[j]) == abs(i - j)) {
				return 0;
			}
		}
	}
	return 1;
}

// Function to parse a solution line
int parse_solution(const char *line, int *solution, int n) {
	int count = 0;
	const char *ptr = line;
	while (*ptr) {
		if (*ptr >= '0' && *ptr <= '9') {
			solution[count++] = *ptr - '0';
		}
		ptr++;
	}
	return count == n;
}

// Tester function
void test_n_queens(int n, const char *program) {
	char command[256];
	snprintf(command, sizeof(command), "%s %d", program, n);

	FILE *fp = popen(command, "r");
	if (!fp) {
		fprintf(stderr, "Failed to execute %s\n", program);
		exit(1);
	}

	char line[1024];
	int solution[n];
	int valid_count = 0, total_count = 0;

	while (fgets(line, sizeof(line), fp)) {
		if (parse_solution(line, solution, n)) {
			total_count++;
			if (is_valid_solution(solution, n)) {
				valid_count++;
			} else {
				printf("Invalid solution: %s", line);
			}
		} else {
			printf("Malformed solution: %s", line);
		}
	}

	pclose(fp);

	printf("Test results for n=%d:\n", n);
	printf("Total solutions: %d\n", total_count);
	printf("Valid solutions: %d\n", valid_count);
	printf("Invalid solutions: %d\n", total_count - valid_count);
	if (total_count == valid_count) {
		printf("All solutions are valid!\n");
	} else {
		printf("Some solutions are invalid.\n");
	}
}

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <program> <n>\n", argv[0]);
		return 1;
	}

	const char *program = argv[1];
	int n = atoi(argv[2]);
	if (n <= 0) {
		fprintf(stderr, "Error: n must be a positive integer\n");
		return 1;
	}
	test_n_queens(n, program);

	return 0;
}

//gcc -o tester n_queens_tester.c
//./tester ./n_queens 7
