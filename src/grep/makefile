COMP = gcc -Wall -Wextra -Werror 

all: s21_grep

s21_grep:
	$(COMP) grep_parsing.c grep_printer.c grep.c -o s21_grep

clean:
	rm s21_grep

rebuild: clean s21_grep