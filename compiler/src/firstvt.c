/**
 * Calculate FIRSTVT of input grammer from stdin,
 * rules are seperated by new line.
 *
 * Input:
 * 	first line: n
 * 	n grammers follow
 *
 * Output:
 * 	FIRSTV of the input
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 20

typedef struct {
	char *right;	// include trailing \0 for easy printing
	int size;			// doesn't count trailing \0
	char left;
} Grammer;

void set_grammer(Grammer *grammer, char left, char *right);
void replace_str(char *s, char *target, char *replacement);

int main() {
	Grammer *grammers;
	int n, size, used;
	printf("Please input the number of input rules (n): ");
	scanf("%d\n", &n);	// read and ignore newlines
	size = n, used = 0;	// used to shrink the allocated space
	if (!(grammers = malloc(sizeof(Grammer) * size))) {
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= n; ++i) {
		char left[2], right[BUFSIZE], buf[BUFSIZE];
		char *bufp = buf;	// pointers used to read string in buf
		int nread;	// used to update bufp
		printf("Please input the %d rule's left (e.g. P -> Abc): ", i);
		fgets(buf, BUFSIZE, stdin);
		// printf("before: %s\n", buf);
		replace_str(buf, "->", "  ");
		replace_str(buf, "|", " ");
		// printf("replace to %s\n", buf);

		sscanf(bufp, "%1s%n", left, &nread);
		bufp += nread;
		// parse each right expression
		while (sscanf(bufp, "%s%n", right, &nread) > 0) {
			bufp += nread;
			// enlarge allocated space if needed
			// no need to copy string in stuct, because they won't be freed
			if (used == size) {
				size += n;
				grammers = realloc(grammers, size * sizeof(Grammer));
			}
			set_grammer(grammers + used, left[0], right);
			printf("%c -> %s\n", grammers[used].left, grammers[used].right);
			++used;
		}
	}

	// printf("size = %d, used = %d\n", size, used);
}

void set_grammer(Grammer *grammer, char left, char *right) {
	grammer->left = left;
	grammer->size = strlen(right);
	if (!grammer->right) {
		free(grammer->right);
	}
	grammer->right = malloc((grammer->size + 1) * sizeof(char));
	strcpy(grammer->right, right);
}

void replace_str(char *s, char *target, char *replacement) {
	char *p;
	int t_size = strlen(target);
	for (p = strstr(s, target); p; p = strstr(p + t_size, target)) {
		strncpy(p, replacement, t_size);	// do not copy trailing \0
	}
}
