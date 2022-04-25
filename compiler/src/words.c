#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 120
#define TOKEN_SIZE BUF_SIZE
#define TABLE_SIZE 100

// 助记符
const int DEF = 1;
const int IF = 2;
const int FOR = 3;
const int WHILE = 4;
const int ASSIGN = 5;
const int EQUAL = 6;
const int PLUS = 7;
const int STAR = 8;
const int POWER = 9;
const int COMMA = 10;
const int LPAR = 11;
const int RPAR = 12;
const int SEMI = 13;
const int ID = 14;
const int INT = 15;
const int STR = 16;

char buf[BUF_SIZE];
int buf_ptr = 0;
int has_next = 0;
char ch;
char token[BUF_SIZE];
int token_ptr = 0;

// return 0 if the token is not a reserved word
int reserve() {
	if (!strcmp("def", token)) {
		return DEF;
	} else if (!strcmp("if", token)) {
		return IF;
	} else if (!strcmp("for", token)) {
		return FOR;
	} else if (!strcmp("while", token)) {
		return WHILE;
	}
	return 0;
}

void get_buf(int reset) {
	// if reset, clear last char
	buf_ptr = !reset;
	// keep last char
	buf[0] = buf[BUF_SIZE - 1];
	for (int i = buf_ptr; i < BUF_SIZE; ++i) {
		buf[i] = getchar();
		if ((signed char) buf[i] == EOF) {
			has_next = 0;
			return;
		}
	}
}

void init() {
	buf_ptr = 0;
	has_next = 1;
	token_ptr = 0;
	get_buf(1);
}

// return 0 if no char to get
int get_char() {
	if (buf_ptr == BUF_SIZE) {
		get_buf(0);
	}
	if ((signed char) buf[buf_ptr] == EOF) {
		return 0;
	}

	return ch = buf[buf_ptr++];
}

int is_blank(unsigned char ch) {
	return ch <= ' ';
}

// get a non-blank char, return 0 if no char to get
int get_nbc() {
	while (get_char() && is_blank(ch));
	return !is_blank(ch);
}

int concat() {
	if (token_ptr == TOKEN_SIZE - 1) return 0;
	token[token_ptr++] = ch;
	token[token_ptr] = '\0';
	return 1;
}

void retract() {
	--buf_ptr;
}

int main(const int argc, const char *argv[]) {
	if (argc == 2) {
		freopen(argv[1], "r", stdin);
	}

	init();
	while (1) {
		token[0] = '\0';
		token_ptr = 0;
		if (!get_nbc()) return 0;

		concat();
		if (isalpha(ch) || ch == '_') {
			while (get_char() && (isalnum(ch) || ch == '_')) {
				if (!concat()) {
					perror("ERR: 标识符过长\n");
					return 1;
				}
			}
			retract();
			int id = reserve();
			if (id) {
				printf("RESERVE\t%d\t%s\n", id, token);
			} else {
				printf("ID\t%d\t%s\n", ID, token);
			}
		} else if (isdigit(ch)) {
			while (get_char() && isdigit(ch)) {
				if (!concat()) {
					perror("ERR: 整数过长\n");
					return 2;
				}
			}
			retract();
			printf("INT\t%d\t%s\n", INT, token);
		} else if (ch == '=') {
			if (get_char() == '=') {
				concat();
				printf("EQUAL\t%d\t%s\n", EQUAL, token);
			} else {
				retract();
				printf("ASSIGN\t%d\t%s\n", ASSIGN, token);
			}
		} else if (ch == '+') {
			printf("PLUS\t%d\t%s\n", PLUS, token);
		} else if (ch == '*') {
			if (get_char() == '*') {
				concat();
				printf("POWER\t%d\t%s\n", POWER, token);
			} else {
				retract();
				printf("STAR\t%d\t%s\n", STAR, token);
			}
		} else if (ch == ',') {
			printf("COMMA\t%d\t%s\n", COMMA, token);
		} else if (ch == '(') {
			printf("LPAR\t%d\t%s\n", LPAR, token);
		} else if (ch == ')') {
			printf("RPAR\t%d\t%s\n", RPAR, token);
		} else if (ch == ':') {
			printf("SEMI\t%d\t%s\n", SEMI, token);
		} else if (ch == '\'') {
			while (get_char() && ch != '\'') {
				if (!concat()) {
					perror("ERR: 字符串常量过长\n");
					return 3;
				}
			}
			printf("STR\t%d\t%s\n", STR, token + 1);
		} else if (!is_blank(ch)) {
			perror("ERR: Unknown token\n");
			fprintf(stderr, "'%d'\n", ch);
			return 4;
		}
	}
}
