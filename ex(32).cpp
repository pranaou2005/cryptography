#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt plaintext using polyalphabetic substitution cipher
void polyalphabetic_encrypt(char plaintext[], char key[], char ciphertext[])
{
    int i, j;
    int key_len = strlen(key);
    int plaintext_len = strlen(plaintext);

    // Encrypt each character in plaintext
    for (i = 0, j = 0; i < plaintext_len; i++, j++) {
        // Wrap around the key if necessary
        if (j >= key_len) {
            j = 0;
        }

        // Calculate shift amount based on current key character
        int shift = toupper(key[j]) - 'A';

        // Encrypt current plaintext character
        if (isupper(plaintext[i])) {
            ciphertext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
        } else if (islower(plaintext[i])) {
            ciphertext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
        } else {
            // Non-alphabetic characters remain unchanged
            ciphertext[i] = plaintext[i];
            j--; // Decrement j to maintain correct key character for next iteration
        }
    }
    ciphertext[i] = '\0';
}

int main()
{
    char plaintext[1000], key[100], ciphertext[1000];

    // Get key input from the user
    printf("Enter key for polyalphabetic substitution cipher (letters only): ");
    scanf("%s", key);

    // Clear input buffer
    while (getchar() != '\n');

    // Get plaintext input from the user
    printf("Enter plaintext to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character from fgets input

    // Encrypt plaintext using polyalphabetic substitution cipher
    polyalphabetic_encrypt(plaintext, key, ciphertext);

    // Output encrypted ciphertext
    printf("Encrypted ciphertext: %s\n", ciphertext);

    return 0;
}

