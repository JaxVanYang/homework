/**
 * Calculate FIRSTVT and LASTVT of input grammer from stdin,
 * rules are seperated by new line.
 *
 * Input:
 * 	first line: n
 * 	n grammers follow
 *
 * Output:
 * 	FIRSTV and LASTVT of the input
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 20
#define CHARSET 128
#define kStackSize 128

typedef struct {
  char *right;  // include trailing \0 for easy printing
  int size;     // doesn't count trailing \0
  char left;
} Grammer;

typedef struct {
  char first, second;
} CharPair;

CharPair pair_stk[kStackSize];
int stk_top = 0;

int non_terminal[CHARSET];
int firstvt[CHARSET][CHARSET];
int lastvt[CHARSET][CHARSET];

void set_grammer(Grammer *grammer, char left, char *right);
void replace_str(char *s, char *target, char *replacement);

int main() {
  Grammer *grammers;
  int n, size, used;
  printf("Please input the number of input rules (n): ");
  scanf("%d", &n);
  while (getchar() != '\n')
    ;  // Read and ignore the rest of the line

  size = n, used = 0;  // used to shrink the allocated space
  if (!(grammers = malloc(sizeof(Grammer) * size))) {
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= n; ++i) {  // Prompts 1 to n, but stores in 0 to n - 1
    char left[2], right[BUFSIZE], buf[BUFSIZE];
    char *bufp = buf;  // pointers used to read string in buf
    int nread;         // used to update bufp
    printf("Please input the %d rule (e.g. P -> Abc): ", i);
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
      // printf("%c -> %s\n", grammers[used].left, grammers[used].right);
      ++used;
    }
  }

  // printf("size = %d, used = %d\n", size, used);

  // Calculate non-terminal
  memset(non_terminal, 0, sizeof(non_terminal));
  for (int i = 0; i < used; ++i) {
    non_terminal[(int)grammers[i].left] = 1;
  }

  // Calculate FIRSTVT
  memset(firstvt, 0, sizeof(firstvt));
  stk_top = 0;
  // Initialize stack
  for (int i = 0; i < used; ++i) {
    char left = grammers[i].left;
    char *right = grammers[i].right;
    int size = grammers[i].size;
    if (!non_terminal[(int)*right]) {  // P -> a...
      firstvt[(int)left][(int)*right] = 1;
      pair_stk[stk_top++] = (CharPair){left, *right};
    }
    if (size >= 2 && non_terminal[(int)right[0]] &&
        !non_terminal[(int)right[1]]) {  // P -> Qa...
      firstvt[(int)left][(int)right[1]] = 1;
      pair_stk[stk_top++] = (CharPair){left, right[1]};
    }
  }
  // Clear stack
  while (stk_top--) {
    char first = pair_stk[stk_top].first;
    char second = pair_stk[stk_top].second;
    for (int i = 0; i < used; ++i) {
      char left = grammers[i].left;
      char right = grammers[i].right[0];
      if (first == right &&
          !firstvt[(int)left][(int)second]) {  // right must be non-terminal
        firstvt[(int)left][(int)second] = 1;
        pair_stk[stk_top++] = (CharPair){left, second};
      }
    }
  }
  // Print FIRSTVT
  for (int i = 0; i < CHARSET; ++i) {
    if (non_terminal[i]) {
      int is_first = 1;
      printf("FIRSTVT(%c) = {", i);
      for (int j = 0; j < CHARSET; ++j) {
        if (firstvt[i][j]) {
          printf("%s%c", is_first ? "" : ", ", j);
          is_first = 0;
        }
      }
      puts("}");
    }
  }

  // Calculate LASTVT
  memset(lastvt, 0, sizeof(lastvt));
  stk_top = 0;
  // Initialize stack
  for (int i = 0; i < used; ++i) {
    char left = grammers[i].left;
    char *right = grammers[i].right;
    int size = grammers[i].size;
    if (!non_terminal[(int)right[size - 1]]) {  // P -> ...a
      lastvt[(int)left][(int)right[size - 1]] = 1;
      pair_stk[stk_top++] = (CharPair){left, right[size - 1]};
    }
    if (size >= 2 && non_terminal[(int)right[size - 1]] &&
        !non_terminal[(int)right[size - 2]]) {  // P -> ...aQ
      lastvt[(int)left][(int)right[size - 2]] = 1;
      pair_stk[stk_top++] = (CharPair){left, right[size - 2]};
    }
  }
  // Clear stack
  while (stk_top--) {
    char first = pair_stk[stk_top].first;
    char second = pair_stk[stk_top].second;
    for (int i = 0; i < used; ++i) {
      char left = grammers[i].left;
      char right = grammers[i].right[grammers[i].size - 1];
      if (first == right &&
          !lastvt[(int)left][(int)second]) {  // right must be non-terminal
        lastvt[(int)left][(int)second] = 1;
        pair_stk[stk_top++] = (CharPair){left, second};
      }
    }
  }
  // Print LASTVT
  for (int i = 0; i < CHARSET; ++i) {
    if (non_terminal[i]) {
      int is_first = 1;
      printf("LASTVT(%c) = {", i);
      for (int j = 0; j < CHARSET; ++j) {
        if (lastvt[i][j]) {
          printf("%s%c", is_first ? "" : ", ", j);
          is_first = 0;
        }
      }
      puts("}");
    }
  }
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
    strncpy(p, replacement, t_size);  // do not copy trailing \0
  }
}
