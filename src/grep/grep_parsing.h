#ifndef GREP_PARSING_H
#define GREP_PARSING_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char *temple;
} flags;

int parse_params(int argc, char **argv, char *short_options, flags *flgs);

void saveTemple(flags *flgs);

void saveTempleF(flags *flgs);

#endif
