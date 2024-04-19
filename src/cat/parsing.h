#ifndef PARSING_H
#define PARSING_H

#include <getopt.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flags;

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], flags *flgs);

#endif