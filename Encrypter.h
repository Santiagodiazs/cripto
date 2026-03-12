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
enum enctryptDecrypt {ENCRYPT, DECRYPT};

int cypherType;
int encryptDecrypt;
FILE* file;
char* filePath;
char* key;

void rotate(char c, int key, long* position);

#endif // ENCRYPTER_H