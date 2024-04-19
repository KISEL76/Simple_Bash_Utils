#include "parsing.h"

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], flags *flgs) {
  int res;
  int error = 0;
  int index = 0;

  while ((res = getopt_long(argc, argv, short_options, long_options, &index)) !=
         -1) {
    switch (res) {
      case 'b':
        flgs->b = 1;
        flgs->n = 1;
        break;
      case 'e':
        flgs->e = 1;
        flgs->v = 1;
        break;
      case 'E':
        flgs->e = 1;
        break;
      case 'n':
        flgs->n = 1;
        break;
      case 's':
        flgs->s = 1;
        break;
      case 't':
        flgs->t = 1;
        flgs->v = 1;
        break;
      case 'T':
        flgs->t = 1;
        break;
      case 'v':
        flgs->v = 1;
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
