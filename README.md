Project 2: Hashing and Passwords

This project implements a password-cracking tool in C using SHA256 hashing. Its goal is to simulate a brute-force attack by comparing a hashed password to potential plaintext guesses. This project helps build an understanding of cryptographic hash functions, password security, and efficient search strategies when the original password is unknown.

Background
Cryptographic hash functions like SHA256 produce a fixed-length output from inputs of arbitrary size. They are deterministic (same input = same output), but their outputs appear random and are hard to reverse-engineer. Many systems store only a hash of a user's password for security. If someone gains access to the password hashes, they must still "crack" the hashes to discover the actual passwords. This program demonstrates how to approach that process by checking password guesses against a known SHA256 hash.

Program Description
The program, called pwcrack, takes one command-line argument: the target SHA256 hash in hex format. It then reads password guesses from standard input, one per line. For each guess, it does the following:

Computes the SHA256 hash and checks for an exact match.

Tries every variant of the guess where exactly one ASCII character is flipped between upper and lower case.

If a match is found, it prints:

pgsql
Copy
Edit
Found password: SHA256(<matching password>) = <hash>
If no match is found, it prints:

arduino
Copy
Edit
Did not find a matching password
Example Usage
pgsql
Copy
Edit
$ ./pwcrack a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd
Password
NeverGuessMe!!
secret
Found password: SHA256(seCret) = a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd
You can also pipe in guesses from a file:

shell
Copy
Edit
$ ./pwcrack a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd < guesses.txt
Note: The tool only tries case variants with one character flipped, not all permutations.

Development Notes
You will use the OpenSSL library and its SHA256 function:

c
Copy
Edit
SHA256(const unsigned char data[], uint64_t count, unsigned char md_buf[]);
To compile:

nginx
Copy
Edit
gcc pwcrack.c -o pwcrack -lcrypto
Sample Code Snippet
c
Copy
Edit
unsigned char hash[32];
SHA256((unsigned char*)input, strlen(input), hash);
for (int i = 0; i < 32; i++) {
    printf("%02x", hash[i]);
}
Testing
You can test your code with real password lists, like the censored version of the RockYou data breach file:

bash
Copy
Edit
./pwcrack < /home/linux/ieng6/cs29fa24/pa2/rockyou_clean.txt
Key Functions (Milestones)
hex_to_byte: Converts two ASCII hex characters into a byte

hexstr_to_hash: Converts a 64-character hex string into a 32-byte hash

check_password: Compares the hash of a given string to a target hash

crack_password: Tries a password and all one-character case variations

Design Insights
This project demonstrates:

How to parse user input and hex formats

How to perform brute-force guessing efficiently

The importance of case sensitivity in passwords

SHA256’s irreversible, deterministic nature

Potential improvements could include trying common substitutions (like "@" for "a"), appending numbers, or applying dictionary-based transformations.

Summary
This password cracker is a hands-on exploration of cryptographic hashing, brute-force attacks, and memory-efficient C programming using OpenSSL. It reinforces how secure password practices help defend against hash-based attacks, and how attackers may still exploit poor password choices.
