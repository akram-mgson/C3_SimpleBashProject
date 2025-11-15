FLAGS = -Wall -Werror -Wextra 

CC = gcc -std=c11 

MAIN_ARTICLES = s21_cat.c s21_cat.h 

all: s21_cat

s21_cat: $(MAIN_ARTICLES)
	$(CC) $(FLAGS) $(MAIN_ARTICLES) -o s21_cat


clean: 
	rm -rf s21_cat

rebuild: clean s21_cat
