#ifndef GREP_PRINTER_H
#define GREP_PRINTER_H

#define _GNU_SOURCE

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep_parsing.h"

void grep(FILE *file, int argc, char *argv, char *temple, flags flgs);

void enterAdd(char *string);

void flagL(regex_t expression, regmatch_t match, FILE *file, char *argv,
           flags flgs);

void flagC(regex_t expression, regmatch_t match, FILE *file, char *argv,
           int argc, flags flgs);

void flagN(regex_t expression, regmatch_t match, FILE *file, char *argv,
           int argc, flags flgs);

void flagV(regex_t expression, regmatch_t match, FILE *file, char *argv,
           int argc);

void flagH(regex_t expression, regmatch_t match, FILE *file);

void flagO(regex_t expression, regmatch_t match, FILE *file, flags flg,
           int argc, char *argv);

void flagIESF(regex_t expression, regmatch_t match, FILE *file, char *argv,
              int argc, flags flgs);

#endif