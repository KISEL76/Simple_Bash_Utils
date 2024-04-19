#include "grep_parsing.h"
#include "grep_printer.h"

int main(int argc, char *argv[]) {
  flags flgs = {0};
  char *short_options = "e:ivclnhsf:o";
  flgs.temple = NULL;
  int c;
  int error = parse_params(argc, argv, short_options, &flgs);
  if (!flgs.e && !flgs.f) {
    flgs.temple = argv[optind];
    c = optind + 1;
  } else {
    c = optind;
  }

  if (error) {
    fprintf(stderr, "ERROR: something wrong with parsing\n");
  } else if (argc - optind == 0 && optind > 0) {
    fprintf(stderr, "ERROR: there is no temple\n");
  } else {
    for (int i = c; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL && !flgs.s) {
        fprintf(stderr, "ERROR: file doesn't exist\n");
      } else if (file == NULL && flgs.s) {
        continue;
      } else {
        grep(file, argc, argv[i], flgs.temple, flgs);
        fclose(file);
      }
    }
  }
  if (flgs.e || flgs.f) free(flgs.temple);
  return error;
}
