#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/sha.h>

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

int main(int argc, char** argv) {
    char hash[32];
    hexstr_to_hash(argv[1], hash);
    printf("User input as hash: \n");
    for (uint8_t i = 0; i < 32; i += 1) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}