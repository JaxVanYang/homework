/**
 * Predictive analysis program for LL(1) grammar
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define EPS "-"
#define ERR ""

typedef struct {
	char *arr;
	size_t size, max_size;
} CharStack;

static CharStack *get_stack() {
	CharStack *ret = (CharStack *) malloc(sizeof(CharStack));
	ret->size = 0;
	ret->max_size = 10;
	ret->arr = (char *) malloc(sizeof(char) * ret->max_size);
	return ret;
}

static void free_stack(CharStack *stk) {
	free(stk->arr);
	free(stk);
}

static void clear(CharStack *stk) {
	stk->size = 0;
}

static char get_top(CharStack *stk) {
	if (stk->size == 0) exit(EXIT_FAILURE);
	return stk->arr[stk->size - 1];
}

static char pop(CharStack *stk) {
	if (stk->size == 0) exit(EXIT_FAILURE);
	char ret = stk->arr[stk->size - 1];
	--stk->size;
	size_t half_size = stk->max_size / 2;
	if (stk->size < half_size) {
		char *new_arr = (char *) malloc(half_size * sizeof(char));
		memcpy(new_arr, stk->arr, stk->size);
		free(stk->arr);
		stk->arr = new_arr;
		stk->max_size = half_size;
	}
	return ret;
}

static void push(CharStack *stk, char ch) {
	stk->arr[stk->size++] = ch;
	size_t double_size = stk->size * 2;
	if (stk->max_size < double_size) {
		char *new_arr = (char *) malloc(double_size * sizeof(char));
		memcpy(new_arr, stk->arr, stk->size);
		free(stk->arr);
		stk->arr = new_arr;
		stk->max_size = double_size;
	}
}

// column terminate symbols for LL(1) analysis table
const static char cols[] = "*(ab^+)#";
int get_nonterminate_id(char ch) {
	int n = strlen(cols);
	for (int i = 0; i < n; ++i) {
		if (cols[i] == ch) return i;
	}
	return -1;
}

// row non-terminate symbols are:
// E = 0, E' = 1, T = 2, T' = 3, F = 4, F' = 5, P = 6
const static char rows[7][3] = {
	"E", "E'", "T", "T'", "F", "F'", "P"};
int get_terminate_id(char ch) {
	if ('0' <= ch && ch <= '6') {
		return ch - '0';
	}
	return -1;
}

// analysis table
const static char table[7][9][5] = {
	{ERR, "21", "21", "21", "21", ERR, ERR, ERR},
	{ERR, ERR, ERR, ERR, ERR, "+0", EPS, EPS, EPS},
	{ERR, "43", "43", "43", "43", ERR, ERR, ERR},
	{ERR, "2", "2", "2", "2", EPS, EPS, EPS},
	{ERR, "65", "65", "65", "65", ERR, ERR, ERR, ERR},
	{"*5", EPS, EPS, EPS, EPS, EPS, EPS, EPS, EPS},
	{ERR, "(0)", "a", "b", "^", ERR, ERR, ERR, ERR}
};

void static help_msg(const char *cmd);
void static parse_arg(const int argc, char *const argv[], FILE **in, int *v);
static void parse_input(FILE *in, const int verbose);

int main(const int argc, char *const argv[]) {
	FILE *in = stdin;
	int verbose = 0;
	parse_arg(argc, argv, &in, &verbose);

	parse_input(in, verbose);
	fclose(in);

	return 0;
}

void static help_msg(const char *cmd) {
	const static char msg[] =
		"Description: Predictive analysis program for LL(1) grammar\n"
		"Usage: %s -f <input_file> -v -h\n"
		"Example: %s -f input.txt -v\n";
	printf(msg, cmd, cmd);
}

void static parse_arg(const int argc, char *const argv[], FILE **in, int *v) {
	const static char optstring[] = "f:vh";
	extern char *optarg;
	extern int optind;
	int c;

	while (~(c = getopt(argc, argv, optstring))) {
		switch (c) {
			case 'f':
				if (!optarg) {
					fprintf(stderr, "Error: expected an argument");
					help_msg(argv[0]);
					exit(EXIT_FAILURE);
				}
				*in = fopen(optarg, "r");
				if (!*in) {
					fprintf(stderr, "Error: file open error");
					help_msg(argv[0]);
					exit(EXIT_FAILURE);
				}
				break;
			case 'v':
				*v = 1;
				break;
			case 'h':
				help_msg(argv[0]);
				exit(EXIT_SUCCESS);
			default:
				fprintf(stderr, "Error: unexpected option");
				help_msg(argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	if (optind < argc) {
		fprintf(stderr, "Error: unexpected argument");
		help_msg(argv[0]);
		exit(EXIT_FAILURE);
	}
}

static void parse_input(FILE *in, const int verbose) {
	ssize_t len, idx;
	size_t size = 0;
	char *line = NULL;
	CharStack *stk = get_stack();

	while ((len = getline(&line, &size, in)) != EOF) {
		idx = 0;
		if (line[len - 1] == '\n') --len;
		line[len] = '\0';
		if (verbose) {
			printf("Log: begin parsing %s\n", line);
		}
		// add place holder after input string
		line[len++] = '#';

		clear(stk);
		push(stk, '#');
		push(stk, '0');
		if (verbose) printf("Log: add terminate %s\n", rows[0]);

		while (idx < len) {
			char a = line[idx];
			char X = get_top(stk);
			if (verbose) printf("Log: a = %c, X = %c\n", a, X);

			if (X == a) {
				if (verbose) puts("Log: a matches X");
				pop(stk);
				++idx;
				continue;
			}

			int r = get_terminate_id(X);
			int c = get_nonterminate_id(a);
			if (r == -1) {
				fprintf(stderr, "Error: unexpected terminate symbol '%c'\n", X);
				exit(EXIT_FAILURE);
			} else if (c == -1) {
				fprintf(stderr, "Error: unexpected non-terminate symbol '%c'\n", a);
				exit(EXIT_FAILURE);
			}

			const char *terminate = rows[r];
			const char *rule = table[r][c];

			if (!strcmp(rule, ERR)) {
				fprintf(stderr, "Error: %s doesn't accept %c\n", terminate, a);
				exit(EXIT_FAILURE);
			}

			if (verbose) {
				printf("Log: push %s -> ", terminate);
				int n = strlen(rule);
				if (n == 0) {
					puts("epsilon");
				} else {
					for (int i = 0; i < n; ++i) {
						int id = get_terminate_id(rule[i]);
						if (id == -1) putchar(rule[i]);
						else printf("%s", rows[id]);
					}
					putchar('\n');
				}
			}

			pop(stk);
			if (strcmp(rule, EPS)) {
				for (int i = strlen(rule) - 1; i >= 0; --i) {
					push(stk, rule[i]);
				}
			}
		}

		if (stk->size) {
			fprintf(stderr, "Error: unparsed production:");
			while (stk->size) {
				char tmp = get_top(stk);
				pop(stk);
				int id = get_terminate_id(tmp);
				if (id != -1) fprintf(stderr, "%s", rows[id]);
				else fprintf(stderr, "%c", tmp);
			}
			fprintf(stderr, "\n");
			exit(EXIT_FAILURE);
		}
			
		line[--len] = '\0';
		printf("Log: parse %s success\n", line);
	}


	free_stack(stk);
	stk = NULL;
}
