# Encrypter

Encrypter is a small command-line C program for applying basic classical ciphers to text files.

## Features

- Rotation cipher support
- Vigenere cipher support
- In-place file processing
- Transposition cipher placeholder for future implementation

## Build

```bash
gcc Encrypter.c -o Encrypter
```

## Usage

```bash
./Encrypter <-r|-v|-t> <-e|-d> <file_path> <key>
```

Example:

```bash
./Encrypter -r -e text.txt 3
```

## Notes

Rotation and transposition cyphers require a numerical key, while Vigenere cypher requires an arbitrary string of aphabetical characters

This project is intended as a simple educational implementation of classic encryption techniques in C.
