#ifndef ENCRYPTER_H
#define ENCRYPTER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// External declarations for getopt (may be needed on some systems)
extern char *optarg;
extern int optind, opterr, optopt;

enum cypherTypes {ROTATING, TRANSPOSITION, VIGENERE};

int cypherType;
char* filePath;
char* key;

#endif // ENCRYPTER_H