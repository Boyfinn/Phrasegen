#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define OPTIONAL_ARGS \
    OPTIONAL_STRING_ARG(seed, "RANDOM", "-s", "seed", "ASCII seed string.")\
    OPTIONAL_STRING_ARG(dict, "words_alpha.txt", "-a", "dictionary", "Text file containing words separated by newline.")\
    OPTIONAL_UINT_ARG(words, 4, "-n", "words", "Number of words to generate.")

#define BOOLEAN_ARGS \
    BOOLEAN_ARG(help, "-h", "Show help")\
    BOOLEAN_ARG(upper, "-U", "Use uppercase")

#include "easyargs.h" //Here

long *plIndices = NULL;
long lIndices = 0;
size_t nCount = 0;
size_t nMaxLen = 1024;
args_t nArgs;

unsigned int HashSeed(char *str);
void BuildIndexTable(FILE* file);
void GeneratePhrase(int words, FILE* file);


#endif
