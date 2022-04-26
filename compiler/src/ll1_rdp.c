/**
 * Recursive descent parser for LL(1) grammar
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

// const static char FOLLOW_E[] = ")";
// const static char FOLLOW_E_[] = ")";
// const static char FOLLOW_T[] = "+)";
const static char FOLLOW_T_[] = "+)";
// const static char FOLLOW_F[] = "(ab^+)";
// const static char FOLLOW_F_[] = "(ab^+)";
// const static char FOLLOW_P[] = "*(ab^+)";

static void help_msg(const char *cmd);
static void parse_arg(const int argc, char *const argv[], FILE **in, int *v);
static void parse_input(FILE *in, const int verbose);

static int is_in(const char ch, const char s[]);
static void E(const char *s, const ssize_t len, int *idp, const int verbose);
static void E_(const char *s, const ssize_t len, int *idp, const int verbose);
static void T(const char *s, const ssize_t len, int *idp, const int verbose);
static void T_(const char *s, const ssize_t len, int *idp, const int verbose);
static void F(const char *s, const ssize_t len, int *idp, const int verbose);
static void F_(const char *s, const ssize_t len, int *idp, const int verbose);
static void P(const char *s, const ssize_t len, int *idp, const int verbose);

int main(const int argc, char *const argv[]) {
	FILE *in = stdin;
	int verbose = 0;
	parse_arg(argc, argv, &in, &verbose);

	parse_input(in, verbose);
	fclose(in);

	return 0;
}

static void help_msg(const char *cmd) {
	const static char msg[] =
		"Description: Recursive descent parser for LL(1) grammar\n"
		"Usage: %s -f <input_file> -v -h\n"
		"Example: %s -f input.txt -v\n";
	printf(msg, cmd, cmd);
}

static void  parse_arg(const int argc, char *const argv[], FILE **in, int *v) {
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
	ssize_t len = EOF;
	size_t size = 0;
	int idx = 0;
	char *line = NULL;

	while ((len = getline(&line, &size, in)) != EOF) {
		// delete \n
		if (line[len - 1] == '\n') {
			line[--len] = '\0';
		}
		// skip empty line
		if (len == 0) continue;
		idx = 0;
		if (verbose) printf("Log: begin parsing %s\n", line);
		E(line, len, &idx, verbose);
		if (verbose) printf("Log: succeed parsing %s\n", line);
	}
}

static int is_in(const char ch, const char s[]) {
	const int n = strlen(s);
	for (int i = 0; i < n; ++i) {
		if (s[i] == ch) return 1;
	}
	return 0;
}

static void E(const char *s, const ssize_t len, int *idp, const int verbose) {
	if (verbose) {
		puts("Log: parsing E->TE'");
		if (*idp < len) printf("Log: current ch = %c\n", s[*idp]);
	}
	T(s, len, idp, verbose);
	E_(s, len, idp, verbose);
}

static void E_(const char *s, const ssize_t len, int *idp, const int verbose) {
	if (verbose) {
		puts("Log: parsing E'->+E|epsilon");
		if (*idp < len) printf("Log: current ch = %c\n", s[*idp]);
	}
	const int idx = *idp;
	if (idx >= len || s[idx] != '+') {
		return;
	}
	++*idp;
	E(s, len, idp, verbose);
}

static void T(const char *s, const ssize_t len, int *idp, const int verbose) {
	if (verbose) {
		puts("Log: parsing T->FT'");
		if (*idp < len) printf("Log: current ch = %c\n", s[*idp]);
	}
	F(s, len, idp, verbose);
	T_(s, len, idp, verbose);
}

static void T_(const char *s, const ssize_t len, int *idp, const int verbose) {
	if (verbose) {
		puts("Log: parsing T'->T|epsilon");
		if (*idp < len) printf("Log: current ch = %c\n", s[*idp]);
	}
	const int idx = *idp;
	if (idx >= len || !is_in(s[idx], FOLLOW_T_)) return;
	T(s, len, idp, verbose);
}

static void F(const char *s, const ssize_t len, int *idp, const int verbose) {
	if (verbose) {
		puts("Log: parsing F->PF'");
		if (*idp < len) printf("Log: current ch = %c\n", s[*idp]);
	}
	P(s, len, idp, verbose);
	F_(s, len, idp, verbose);
}

static void F_(const char *s, const ssize_t len, int *idp, const int verbose) {
	if (verbose) {
		puts("Log: parsing F'->*F'|epsilon");
		if (*idp < len) printf("Log: current ch = %c\n", s[*idp]);
	}
	const int idx = *idp;
	if (idx >= len || s[idx] != '*') return;
	++*idp;
	F_(s, len, idp, verbose);
}

static void P(const char *s, const ssize_t len, int *idp, const int verbose) {
	if (verbose) {
		puts("Log: parsing P->(E)|a|b|^");
		if (*idp < len) printf("Log: current ch = %c\n", s[*idp]);
	}
	int idx = *idp;
	if (idx >= len) {
		fprintf(stderr, "Error: expected more input\n");
		exit(EXIT_FAILURE);
	}

	switch (s[idx]) {
		case '(':
			++*idp;
			E(s, len, idp, verbose);
			idx = *idp;
			if (idx >= len || s[idx] != '(') {
				fprintf(stderr, "Error: expected (\n");
				exit(EXIT_FAILURE);
			}
			break;
		case 'a':
		case 'b':
		case '^':
			++*idp;
			break;
		default:
			fprintf(stderr, "Error: ch = %c, expected (, a, b or ^\n", s[idx]);
			exit(EXIT_FAILURE);
	}
}
