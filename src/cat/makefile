COMP = gcc -Wall -Wextra -Werror 

all: s21_cat

s21_cat:
	$(COMP) parsing.c printer.c cat.c -o s21_cat

clean:
	rm s21_cat

rebuild: clean s21_cat
