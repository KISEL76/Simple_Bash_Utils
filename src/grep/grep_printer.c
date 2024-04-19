#include "grep_printer.h"

void enterAdd(char *line) {
  if (strstr(line, "\n") == NULL) {
    putchar('\n');
  }
}

void flagL(regex_t expression, regmatch_t match, FILE *file, char *argv,
           flags flgs) {
  char *line = NULL;
  size_t len = 0;
  int res = 0;

  while ((res = getline(&line, &len, file)) != -1) {
    if (regexec(&expression, line, 1, &match, 0) == 0 && flgs.v == 0) {
      printf("%s\n", argv);
      break;
    } else if (regexec(&expression, line, 1, &match, 0) != 0 && flgs.v == 1) {
      printf("%s\n", argv);
      break;
    }
  }
  free(line);
}

void flagC(regex_t expression, regmatch_t match, FILE *file, char *argv,
           int argc, flags flgs) {
  int counter = 0;
  int reverseCounter = 0;
  char *line = NULL;
  size_t len = 0;
  int res = 0;

  while ((res = getline(&line, &len, file)) != -1) {
    if (regexec(&expression, line, 1, &match, 0) == 0 && flgs.v == 0) {
      counter++;
    } else if (regexec(&expression, line, 1, &match, 0) != 0 && flgs.v == 1) {
      reverseCounter++;
    }
  }
  if ((argc - optind > 2) && flgs.v == 0 && flgs.l == 0)
    printf("%s:%d\n", argv, counter);
  else if ((argc - optind > 2) && flgs.v == 1 && flgs.l == 0)
    printf("%s:%d\n", argv, reverseCounter);
  else if ((argc - optind > 2) && flgs.l == 1 && flgs.v == 0 && counter > 0)
    printf("%s:%d\n%s\n", argv, 1, argv);
  else if (flgs.l == 1 && flgs.v == 0 && counter > 0)
    printf("%d\n%s\n", 1, argv);
  else if (flgs.l == 1 && flgs.v == 0 && counter == 0)
    printf("%d\n", counter);
  else if (flgs.l == 1 && flgs.v == 1 && reverseCounter > 0)
    printf("%d\n%s\n", 1, argv);
  else if (flgs.l == 1 && flgs.v == 1 && reverseCounter == 0)
    printf("%d\n", reverseCounter);
  else if (flgs.v == 1 && flgs.l == 0)
    printf("%d\n", reverseCounter);
  else
    printf("%d\n", counter);
  free(line);
}

void flagN(regex_t expression, regmatch_t match, FILE *file, char *argv,
           int argc, flags flgs) {
  int line_num = 0;
  char *line = NULL;
  size_t len = 0;
  int res = 0;

  while ((res = getline(&line, &len, file)) != -1) {
    line_num++;
    if (regexec(&expression, line, 1, &match, 0) == 0 && flgs.v == 0) {
      if (argc - optind > 2) printf("%s:", argv);
      printf("%d:%s", line_num, line);
      enterAdd(line);
    } else if (regexec(&expression, line, 1, &match, 0) != 0 && flgs.v == 1) {
      if (argc - optind > 2) printf("%s:", argv);
      printf("%d:%s", line_num, line);
      enterAdd(line);
    }
  }
  free(line);
}

void flagV(regex_t expression, regmatch_t match, FILE *file, char *argv,
           int argc) {
  char *line = NULL;
  size_t len = 0;
  int res = 0;

  while ((res = getline(&line, &len, file)) != -1) {
    if (regexec(&expression, line, 1, &match, 0) != 0) {
      if (argc - optind > 2) printf("%s:", argv);
      printf("%s", line);
      enterAdd(line);
    }
  }
  free(line);
}

void flagH(regex_t expression, regmatch_t match, FILE *file) {
  char *line = NULL;
  size_t len = 0;
  int res = 0;

  while ((res = getline(&line, &len, file)) != -1) {
    if (regexec(&expression, line, 1, &match, 0) == 0) {
      printf("%s", line);
      enterAdd(line);
    }
  }
  free(line);
}

void flagO(regex_t expression, regmatch_t match, FILE *file, flags flgs,
           int argc, char *argv) {
  char *line = NULL;
  int line_num = 0;
  int num_used = 0;
  size_t len = 0;
  int res = 0;

  while ((res = getline(&line, &len, file)) != -1) {
    if (flgs.n == 1 && flgs.v == 0) {
      line_num++;
      num_used = line_num;
    } else if (flgs.n == 1 && flgs.v == 1) {
      line_num++;
    } else {
      line_num++;
      num_used = line_num;
    }
    if (flgs.v == 0) {
      int offset = 0;
      while (regexec(&expression, line + offset, 1, &match, 0) == 0) {
        if (flgs.n == 0) {
          if ((argc - optind > 2) && (num_used == line_num)) {
            printf("%s:%.*s\n", argv, (int)(match.rm_eo - match.rm_so),
                   line + offset + match.rm_so);
            num_used++;
          } else {
            printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                   line + offset + match.rm_so);
          }
        } else if (flgs.n == 1) {
          if (num_used == line_num) {
            printf("%d:%.*s\n", line_num, (int)(match.rm_eo - match.rm_so),
                   line + offset + match.rm_so);
            num_used++;
          } else {
            printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                   line + offset + match.rm_so);
          }
        }
        offset += match.rm_eo;
        enterAdd(line);
      }
    } else {
      if (regexec(&expression, line, 1, &match, 0) != 0 && flgs.n) {
        if (argc - optind > 2) printf("%s:", argv);
        printf("%d:%s", line_num, line);
        enterAdd(line);
      }
    }
  }
  free(line);
}

void flagIESF(regex_t expression, regmatch_t match, FILE *file, char *argv,
              int argc, flags flgs) {
  int res = 0;
  char *line = NULL;
  size_t len = 0;
  while ((res = getline(&line, &len, file)) != -1) {
    if (regexec(&expression, line, 1, &match, 0) == 0) {
      if (flgs.e || flgs.f) {
        if (argc - optind > 1) printf("%s:", argv);
      } else {
        if (argc - optind > 2) printf("%s:", argv);
      }
      printf("%s", line);
      enterAdd(line);
    }
  }
  free(line);
}

void grep(FILE *file, int argc, char *argv, char *temple, flags flgs) {
  regex_t expression;
  regmatch_t match;
  memset(&match, 0, sizeof(regmatch_t));
  int error;
  error = regcomp(&expression, temple, REG_EXTENDED | (flgs.i ? REG_ICASE : 0));
  if (error) {
    fprintf(stderr, "ERROR: something wrong with compilation of expression\n");
    regfree(&expression);
  } else {
    // DEFAULT FLAG I FLAG E FLAG S FLAG F
    if (flgs.c == 0 && flgs.h == 0 && flgs.l == 0 && flgs.n == 0 &&
        flgs.o == 0 && flgs.v == 0) {
      flagIESF(expression, match, file, argv, argc, flgs);
    }
    // FLAG L
    else if (flgs.l == 1 && flgs.c == 0)
      flagL(expression, match, file, argv, flgs);
    // FLAG C
    else if (flgs.c == 1)
      flagC(expression, match, file, argv, argc, flgs);
    // FLAG N
    else if (flgs.n == 1 && flgs.o == 0)
      flagN(expression, match, file, argv, argc, flgs);
    // FLAG V
    else if (flgs.v == 1 && flgs.c == 0 && flgs.l == 0 && flgs.n == 0)
      flagV(expression, match, file, argv, argc);
    // FLAG H
    else if (flgs.h == 1 && flgs.o == 0)
      flagH(expression, match, file);
    // FLAG O
    else if (flgs.o == 1)
      flagO(expression, match, file, flgs, argc, argv);

    regfree(&expression);
  }
}
