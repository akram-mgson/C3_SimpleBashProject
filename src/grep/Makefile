FLAGS = -Wall -Werror -Wextra

CC = gcc -std=c11

MAIN_ARTICLES = s21_grep.c s21_grep.h

all: s21_grep

s21_grep: $(MAIN_ARTICLES)
	$(CC) $(FLAGS) $(MAIN_ARTICLES) -o s21_grep


clean:
	rm -rf s21_grep

rebuild: clean s21_grep
