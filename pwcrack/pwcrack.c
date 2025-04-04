#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/sha.h>
#include <ctype.h>

const int SHA_LENGTH = 32;

// Function to calculate the average of numbers provided as commandline arguments
void calculate_average(int argc, char** argv) {
    double sum = 0.0;
    int i; // Declare the loop variable outside
    for (i = 1; i < argc; i++) {
        sum += atof(argv[i]);
    }
    double average = sum / (argc - 1);
    printf("Average: %.2f\n", average);
}

// Function to convert hex characters to a byte
uint8_t hex_to_byte(unsigned char h1, unsigned char h2) {
    return (h1 >= 'a' ? h1 - 'a' + 10 : h1 - '0') * 16 + (h2 >= 'a' ? h2 - 'a' + 10 : h2 - '0');
}

// Function to convert hex string to SHA256 hash
void hexstr_to_hash(char hexstr[], unsigned char hash[SHA_LENGTH]) {
    int i;  // Declare the loop variable outside
    for (i = 0; i < 64; i += 2) {
        hash[i / 2] = hex_to_byte(hexstr[i], hexstr[i + 1]);
    }
}

// Function to check if the provided password matches the given hash
int8_t check_password(char password[], unsigned char given_hash[SHA_LENGTH]) {
    unsigned char hash[SHA_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);
    return memcmp(hash, given_hash, SHA_LENGTH) == 0;
}

// Function to attempt cracking the password by checking case variations
int8_t crack_password(char original_password[], unsigned char given_hash[]) {
    size_t i;  // Loop variable for traversing the password
    size_t length = strlen(original_password);
    char password[256];

    for (i = 0; i < length; i++) {
        // Check lowercase
        strcpy(password, original_password);
        password[i] = tolower(original_password[i]);
        if (check_password(password, given_hash)) {
            strcpy(original_password, password); // Preserve the found password
            return 1;
        }

        // Check uppercase
        strcpy(password, original_password);
        password[i] = toupper(original_password[i]);
        if (check_password(password, given_hash)) {
            strcpy(original_password, password); // Preserve the found password
            return 1;
        }
    }
    return 0;
}

// Main function to handle command-line arguments and password input
int main(int argc, char** argv) {
    // Calculate average if more than one number is provided
    if (argc > 2) {
        calculate_average(argc, argv);
    }

    unsigned char hash[SHA_LENGTH];
    hexstr_to_hash(argv[1], hash);

    char password[256];
    while (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }

        int i; // Declare the loop variable outside
        if (check_password(password, hash) || crack_password(password, hash)) {
            printf("Found password: SHA256(%s) = ", password);
            for (i = 0; i < SHA_LENGTH; i++) {
                printf("%02x", hash[i]);
            }
            printf("\n");
            return 0;
        }
    }

    printf("Did not find a matching password\n");
    return 0;
}
