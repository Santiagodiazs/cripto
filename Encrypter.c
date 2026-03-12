#include "Encrypter.h"



int main(int argc, char* argv[]) {

    if(argc != 5) {
        printf("Use: <Cypher_type (-r, -t, -v)> <Encrypt/Decrypt (-e, -d)> <File_path> <Key>\n");
        return 1;
    }

    int opt;
    
    // Parse the cipher type option
    while((opt = getopt(argc, argv, "rvted")) != -1) {
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
            case 'd':
                encryptDecrypt = DECRYPT;
                break;
            case 'e':
                encryptDecrypt = ENCRYPT;
                break;
            case '?':
                printf("Available cyphers -r (Rotating) -v (Vigenere) -t (Transposition)\n");
                printf("Available operations -e (Encrypt) -d (Decrypt)\n");
                return 1;
        }
    }

    // Get file path and key from remaining arguments
    if(optind + 1 >= argc) {
        printf("Error: Missing file path and/or key\n");
        printf("Use: <Cypher_type (-r, -t, -v)> <Encrypt/Decrypt (-e, -d)> <File_path> <Key>\n");
        return 1;
    }
    
    filePath = argv[optind];     // First remaining argument is file path
    key = argv[optind + 1];      // Second remaining argument is key

    long* position = malloc(sizeof(long));

    file = fopen(filePath, "r+");
    if(file == NULL) {
        printf("Error opening the file, make sure it exists");
        return 1;
    }

    //Logic for rotating cypher
    if(cypherType == ROTATING) {
        int realKey = atoi(key);
        if(realKey == 0) {
                printf("Please enter a number as key for the rotating cypher");
                return 1;
        }
        char c;
        
        if(encryptDecrypt == ENCRYPT) {
            while((c = fgetc(file)) != EOF) {
                rotate(c, realKey, position);
            }
        } else {
            while((c = fgetc(file)) != EOF) {
                rotate(c, 26 - realKey, position);
            }
        }
    }

    if(cypherType == VIGENERE) {
        int keyLength = strlen(key);
        for(int i = 0; i < keyLength; i++) {
            if(isalpha(key[i])) {
                key[i] = tolower(key[i]); 
            } else {
                printf("Please enter a valid key for the Vigenere cypher (only letters)");
                return 1;
        }
        char c;
        int keyIndex = 0;
        if(encryptDecrypt == ENCRYPT) {
            
            while((c = fgetc(file)) != EOF) {
                if(isalpha(c)) {
                    int keyShift = key[keyIndex % keyLength] - 'a';
                    rotate(c, keyShift, position);
                    keyIndex++;
                }
            }
        } else {
            while((c = fgetc(file)) != EOF) {
                if(isalpha(c)) {
                    int keyShift = key[keyIndex % keyLength] - 'a';
                    rotate(c, 26 - keyShift, position);
                    keyIndex++;
                }
            }
        }
    }
    }

    fclose(file);
    return 0;
}

void rotate(char c, int key, long* position) {
    char encrypted = c;
                if(c >= 'a' && c <= 'z'){
                    encrypted = (c - 'a' + key) % 26 + 'a';
                }
                else if(c >= 'A' && c <= 'Z') {
                    encrypted = (c - 'A' + key) % 26 + 'A';
                }
            
                *position = ftell(file);     // Save current position
                fseek(file, *position - 1, SEEK_SET);  // Go back to overwrite
                fputc(encrypted, file);     // Write encrypted character
                fseek(file, *position, SEEK_SET);      // Return to reading position
}