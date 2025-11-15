#ifndef S21_GREP_H
#define S21_GREP_H

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char* pattern;
} arguments;

arguments arguments_parser(int argc, char* argv[]);
void major(arguments arg, int argc,
           char** argv);  // Добавлено объявление функции
void add_patt2(arguments* arg, const char* filepath);
void check_line(char* line, int n);
void read_files(arguments arg, char* path, regex_t* reg);
void pattern_add(arguments* arg, char* pattern);

#endif  // S21_GREP_H