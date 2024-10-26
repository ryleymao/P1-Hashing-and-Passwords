#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/sha.h>

// https://stackoverflow.com/questions/735126/are-there-alternate-implementations-of-gnu-getline-interface/735472#735472
size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

uint8_t hex_to_byte(unsigned char h1, unsigned char h2) {
    return (((h1 % 32 + 9) % 25) * 16) + ((h2 % 32 + 9) % 25);
}

void hexstr_to_hash(unsigned char hexstr[], char hash[32]) {
    // store current location of hexstr, to read by pairs
    char* ptr = hexstr;
    for (uint8_t i = 0; i < 32; i += 1) {
        unsigned int tmp;
        // read two characters from hexstr, format ("0x...") and save to tmp
        sscanf(ptr, "%2x", &tmp);
        // save to hash and move ptr
        hash[i] = tmp;
        ptr += 2;
    }
}

int8_t check_password(char password[], char given_hash[32]) {
    char hash[32];
    //assuming password is null terminated
    SHA256(password, strlen(password), hash);

    for (uint8_t i = 0; i < 32; i += 1) {
        if (hash[i] != given_hash[i]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    char hash[32];
    hexstr_to_hash(argv[1], hash);

    char* password;
    size_t size;

    while (getline(&password, &size, stdin) != -1) {
        int8_t result = check_password(password, hash);
        if (result == 1) {
            printf("Found password: SHA256(%s) = %s", password, argv[1]);
            exit(0);
        }
    }
    printf("Did not find a matching password");
}