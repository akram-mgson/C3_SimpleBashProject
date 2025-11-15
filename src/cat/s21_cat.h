#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;
} Options;

Options parser(int argc, char *argv[]);
void Flags_Mission(FILE *file, Options *options);
void table_flags(char s, Options *options);

#endif  // CAT_H