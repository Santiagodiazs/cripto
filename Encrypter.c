#include "Encrypter.h"

int main(int argc, char* argv[]) {

    if(argc != 4) {
        printf("Use: <Cypher_type (-r, -t, -v)> <File_path> <Key>\n");
        return 1;
    }

    int opt;
    
    // Parse the cipher type option
    while((opt = getopt(argc, argv, "rvt")) != -1) {
        switch(opt) {
            case 'r':
                cypherType = ROTATING;
                break;
            case 'v':
                cypherType = VIGENERE;
                break;
            case 't':
                cypherType = TRANSPOSITION;
                break;
            case '?':
                printf("Available cyphers -r (Rotating) -v (Vigenere) -t (Transposition)\n");
                return 1;
        }
    }

    // Get file path and key from remaining arguments
    if(optind + 1 >= argc) {
        printf("Error: Missing file path and/or key\n");
        printf("Use: <Cypher_type (-r, -t, -v)> <File_path> <Key>\n");
        return 1;
    }
    
    filePath = argv[optind];     // First remaining argument is file path
    key = argv[optind + 1];      // Second remaining argument is key

    FILE* file = fopen(filePath, "r+");
    if(file == NULL) {
        printf("Error opening the file, make sure it exists");
        return 1;
    }

    if(cypherType == ROTATING) {
        int realKey = atoi(key);
        if(realKey == 0) {
            printf("Please enter a number as key for the rotating cypher");
            return 1;
        }

        char c;
        while((c = fgetc(file)) != EOF) {
             if(c >= 'a' && c <= 'z'){
                c = (c - 'a' + realKey) % 26 + 'a';
                fputs(&c, file);
             }
             if(c >= 'A' && c <= 'Z') {
                c = (c - 'A' + realKey) % 26 + 'A';
                fputs(&c, file);
             }
        }
    }

    fclose(file);
    return 0;
}