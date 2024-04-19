#include "grep_parsing.h"

void saveTemple(flags *flgs) {
  if (flgs->temple == NULL) {
    flgs->temple = (char *)malloc((strlen(optarg) + 1) * sizeof(char));
    strcpy(flgs->temple, optarg);
  } else {
    flgs->temple = (char *)realloc(
        flgs->temple,
        (strlen(flgs->temple) + strlen(optarg) + 2) * sizeof(char));
    strcat(flgs->temple, "|");
    strcat(flgs->temple, optarg);
  }
}

void saveTempleF(flags *flgs) {
  char *line = NULL;
  size_t len = 0;
  FILE *file = fopen(optarg, "r");
  if (file != NULL) {
    int res = 0;
    while ((res = getline(&line, &len, file)) != -1) {
      int length = strlen(line);
      if (flgs->temple == NULL) {
        if (strstr(line, "\n") != 0) line[length - 1] = '\0';
        flgs->temple = (char *)malloc((length + 1) * sizeof(char));
        strcpy(flgs->temple, line);
      } else {
        flgs->temple = (char *)realloc(
            flgs->temple, (strlen(flgs->temple) + length + 2) * sizeof(char));
        if (strstr(line, "\n") != 0) line[length - 1] = '\0';
        strcat(flgs->temple, "|");
        strcat(flgs->temple, line);
      }
    }
    free(line);
    fclose(file);
  } else {
    fprintf(stderr, "ERROR: temple file doesn't exist\n");
  }
}

int parse_params(int argc, char **argv, char *short_options, flags *flgs) {
  int res;
  int error = 0;
  while ((res = getopt_long(argc, argv, short_options, NULL, NULL)) != -1) {
    switch (res) {
      case 'i':
        flgs->i = REG_ICASE;
        break;
      case 'e':
        flgs->e = REG_EXTENDED;
        saveTemple(flgs);
        break;
      case 'v':
        flgs->v = 1;
        break;
      case 'c':
        flgs->c = 1;
        break;
      case 'l':
        flgs->l = 1;
        break;
      case 'n':
        flgs->n = 1;
        break;
      case 'h':
        flgs->h = 1;
        break;
      case 's':
        flgs->s = 1;
        break;
      case 'f':
        flgs->f = 1;
        saveTempleF(flgs);
        break;
      case 'o':
        flgs->o = 1;
        break;
      case '?':
        error = 1;
        break;
      default:
        error = 1;
        break;
    }
  }
  return error;
}