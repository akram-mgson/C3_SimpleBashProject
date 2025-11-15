#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Options options = parser(argc, argv);

  if (optind == argc) {
    Flags_Mission(stdin, &options);
  } else {
    for (int i = optind; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (!file) {
        perror(argv[i]);
        continue;
      }
      Flags_Mission(file, &options);
      fclose(file);
    }
  }

  return 0;
}
Options parser(int argc, char *argv[]) {
  int flags;
  Options options = {0};
  const char *short_options = "bensvtET";
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {0, 0, 0, 0}};

  while ((flags = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (flags) {
      case 'b':
        options.b = 1;
        break;
      case 'e':
        options.e = 1;
        options.v = 1;
        break;
      case 'n':
        options.n = 1;
        break;
      case 's':
        options.s = 1;
        break;
      case 't':
        options.t = 1;
        options.v = 1;
        break;
      case 'v':
        options.v = 1;
        break;
      case 'E':
        options.E = 1;
        break;
      case 'T':
        options.T = 1;
        break;
      default:
        fprintf(stderr, "Usage: %s [-bensvtET] [file ...]\n", argv[0]);
        break;
    }
  }
  return options;
}

void Flags_Mission(FILE *file, Options *options) {
  int maj_line = 1;
  int previous = '\n';
  int other = 0;
  int symbol = 1;

  for (int s = fgetc(file); s != EOF; s = fgetc(file)) {
    if (options->s && s == '\n' && previous == '\n') {
      other++;

      if (other > 1) {
        continue;
      }
    } else {
      other = 0;
    }

    if (options->n && (symbol || previous == '\n')) {
      if (!options->b || s != '\n') {
        printf("%6d\t", maj_line++);
      }
    }

    if (options->b && previous == '\n' && s != '\n') {
      printf("%6d\t", maj_line++);
    }

    table_flags(s, options);
    previous = s;
    symbol = 0;
  }
}

void table_flags(char s, Options *options) {
  if (options->v) {
    if (s < 32 && s != '\n' && s != '\t') {
      printf("^%c", s + 64);
      return;
    } else if (s == 127) {
      printf("^?");
      return;
    }
  }

  if (options->t && s == '\t') {
    printf("^I");
    return;
  }

  if (options->e && s == '\n') {
    printf("$\n");
    return;
  }

  if (options->E && s == '\n') {
    printf("$\n");
    return;
  }

  if (options->T && s == '\t') {
    printf("^I");
    return;
  }

  printf("%c", s);
}