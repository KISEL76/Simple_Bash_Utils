#include "printer.h"

void cat(int argc, char** argv, flags flgs) {
  int is_empty = 0, line_num = 1;
  int ch;
  for (int i = optind; i < argc; i++) {
    FILE* file = fopen(argv[i], "r");
    if (file == NULL) {
      fprintf(stderr, ("ERROR: %s doesn't exist!\n"), argv[i]);
    } else {
      for (char prev = '\n'; (ch = fgetc(file)) != EOF; prev = ch) {
        if (flgs.s == 1) {
          if (prev == '\n' && ch == '\n') {
            if (is_empty == 1) {
              continue;
            }
            is_empty = 1;
          } else {
            is_empty = 0;
          }
        }
        if (flgs.n == 1 && (!flgs.b || ch != '\n') && prev == '\n') {
          printf("%6d\t", line_num);
          line_num++;
        }
        if (flgs.e && ch == '\n') {
          printf("$");
        }
        if (flgs.t && ch == '\t') {
          printf("^");
          ch = ch + 64;
        }
        if (flgs.v == 1) {
          if ((ch <= 8 && ch >= 0) || (ch >= 11 && ch <= 31)) {
            printf("^");
            ch = ch + 64;
          } else if (ch == 127) {
            printf("^");
            ch = ch - 64;
          }
        }
        printf("%c", ch);
      }
      fclose(file);
    }
    line_num = 1;
  }
}
