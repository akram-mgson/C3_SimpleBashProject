#include "s21_grep.h"

int main(int argc, char** argv) {
  arguments arg = arguments_parser(argc, argv);
  if (!arg.pattern) {
    fprintf(stderr, "no pattern\n");

  } else {
    if (argc - optind == 1) arg.h = 1;
    major(arg, argc, argv);
  }
  return 0;
}

void pattern_add(arguments* arg, char* pattern) {
  if (arg->pattern == NULL) {
    arg->pattern = strdup(pattern);
    if (arg->pattern == NULL) {
      perror("strdup");
    }
  } else {
    char* new_pattern = malloc(strlen(arg->pattern) + strlen(pattern) + 2);
    if (new_pattern == NULL) {
      perror("malloc");
    } else {
      strcpy(new_pattern, arg->pattern);
      strcat(new_pattern, "|");
      strcat(new_pattern, pattern);
      free(arg->pattern);
      arg->pattern = new_pattern;
    }
  }
}

void add_patt2(arguments* arg, const char* filepath) {
  FILE* f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s) perror(filepath);
  } else {
    char* line = NULL;
    size_t memlen = 0;
    ssize_t read;
    while ((read = getline(&line, &memlen, f)) != -1) {
      if (line[read - 1] == '\n') line[read - 1] = '\0';
      pattern_add(arg, line);
    }
    free(line);
    fclose(f);
  }
}

arguments arguments_parser(int argc, char* argv[]) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        pattern_add(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_patt2(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
      default:
        fprintf(stderr, "Usage: %s [-eivclnhsf:o] [file ...]\n", argv[0]);
        break;
    }
  }
  if (arg.pattern == NULL && optind < argc) {
    arg.pattern = argv[optind++];
  }
  return arg;
}

void check_line(char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
}

void read_files(arguments arg, char* path, regex_t* reg) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    return;
  }

  char* line = NULL;
  size_t memlen = 0;
  int line_count = 1;
  int fl_count = 0;
  ssize_t read;

  while ((read = getline(&line, &memlen, f)) != -1) {
    regmatch_t sym;
    int fin = regexec(reg, line, 1, &sym, 0);
    if ((fin == 0 && !arg.v) || (arg.v && fin != 0)) {
      if (arg.c) {
        fl_count++;
      } else if (arg.l) {
        printf("%s\n", path);
        break;
      } else {
        if (arg.n) printf("%d:", line_count);
        if (!arg.h) printf("%s:", path);
        if (arg.o) {
          for (int i = sym.rm_so; i < sym.rm_eo; i++) {
            putchar(line[i]);
          }
          putchar('\n');
        } else {
          check_line(line, read);
        }
      }
    }
    line_count++;
  }

  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", fl_count);
  }

  free(line);
  fclose(f);
}

void major(arguments arg, int argc, char** argv) {
  regex_t res;
  int error = 0;
  if (arg.i) {
    error = regcomp(&res, arg.pattern, REG_EXTENDED | REG_ICASE);
  } else {
    error = regcomp(&res, arg.pattern, REG_EXTENDED);
  }
  if (error) {
    perror("regcomp");
  }
  {
    for (int i = optind; i < argc; i++) {
      read_files(arg, argv[i], &res);
    }

    regfree(&res);
  }
}