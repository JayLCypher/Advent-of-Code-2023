//LINT_C_FILE

#include <stdio.h>

#if __STDC_VERSION__ < 202311L
#define nullptr (void*)0
#endif

const char *pop_argv(int *argc, char **argv[*argc]) {
	if (*argc == 0 || !argv) { return nullptr; }
	const char *ret = *argv[0];
	*argc -= 1;
	*argv += 1;
	return ret;
}

size_t day1_part1(const char *line) {
	if (!*line) { return 0; }
	size_t digits_encountered = 0;
	size_t a = 0, b = 0;
	do {
		if (*line < '0' || *line > '9') { continue; } // Skip ascii non-digit

		if (digits_encountered == 0) { a = *line & 0xF; ++digits_encountered; } // First digit
		else { b = *line & 0xF; ++digits_encountered; } // Last digit
	} while (*line++);
	if (digits_encountered == 1) { b = a; } // Dup a if only 1 digit encountered.
	return (a * 10) + b; // Move a by 10 in decimal space
}

int main(int argc, char *argv[argc]) {
	// Hello!
	printf("Welcome to day 1 of AoC!\n");
	const char *program = pop_argv(&argc, &argv);
	if (argc < 1) {
		fprintf(stderr, "ERROR: Expected input. Usage: ./day1 <input file path>\n");
		return 1;
	}
	// Get the file
	const char *file_path = pop_argv(&argc, &argv);
	FILE *const f = fopen(file_path, "r");
	if (!f) {
		fprintf(stderr, "ERROR: Cannot open file with path: %s\n", file_path);
		return 1;
	}

	size_t result = 0;
	// Need to read the file
	char buf[512] = {0};
	while (feof(f) == 0) {
		fscanf(f, "%s\n", buf);
		result += day1_part1(buf);
		for (size_t i = 0; i < 512; ++i) { buf[i] = '\0'; }
	}

	fclose(f);
	printf("Result: %zu\n", result);

	return 0;
}
