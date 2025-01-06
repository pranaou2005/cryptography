#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the greatest common divisor (GCD) using Euclid's algorithm
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular inverse of a modulo m using extended Euclidean algorithm
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

// Function to decrypt affine cipher given parameters a and b
void affine_decrypt(int a, int b, char ciphertext[], char plaintext[]) {
    int i;
    int len = strlen(ciphertext);

    // Calculate modular inverse of a modulo 26
    int a_inv = mod_inverse(a, ALPHABET_SIZE);
    if (a_inv == -1) {
        printf("Modular inverse of %d does not exist. Cannot decrypt.\n", a);
        return;
    }

    // Decrypt each character in the ciphertext
    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char c = ciphertext[i];
            if (isupper(c)) {
                plaintext[i] = 'A' + ((a_inv * (c - 'A' - b + ALPHABET_SIZE)) % ALPHABET_SIZE);
            } else {
                plaintext[i] = 'a' + ((a_inv * (c - 'a' - b + ALPHABET_SIZE)) % ALPHABET_SIZE);
            }
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[1000];
    char plaintext[1000];
    int freq1 = 'B' - 'A'; // Index of most frequent letter 'B'
    int freq2 = 'U' - 'A'; // Index of second most frequent letter 'U'

    printf("Enter ciphertext to decrypt: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character from input

    // Calculate parameters a and b using known frequencies
    // Assume 'B' corresponds to 'E' and 'U' corresponds to 'T' in English frequency analysis
    int a = (freq1 - freq2 + ALPHABET_SIZE) % ALPHABET_SIZE;
    int b = (freq1 - 'E' + ALPHABET_SIZE) % ALPHABET_SIZE; // 'E' is the most common letter in English

    printf("Guessed values: a = %d, b = %d\n", a, b);

    // Decrypt the ciphertext using guessed parameters
    affine_decrypt(a, b, ciphertext, plaintext);

    // Output decrypted plaintext
    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}

