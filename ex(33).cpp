#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to prepare the key and fill the matrix
void prepare_key(char key[], char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j, k;
    char *ptr;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Note: 'J' is omitted (I and J are treated as the same)

    // Convert key to uppercase
    for (ptr = key; *ptr != '\0'; ptr++) {
        *ptr = toupper(*ptr);
    }

    // Remove any duplicate letters from the key
    for (i = 0; i < strlen(key); i++) {
        for (j = i + 1; key[j] != '\0'; j++) {
            if (key[i] == key[j]) {
                for (k = j; key[k] != '\0'; k++) {
                    key[k] = key[k + 1];
                }
            }
        }
    }

    // Initialize matrix with key
    ptr = key;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (*ptr != '\0') {
                matrix[i][j] = *ptr++;
            } else {
                // Fill the rest of the matrix with remaining alphabet letters
                while (strchr(key, alphabet[k]) != NULL) {
                    k++;
                }
                matrix[i][j] = alphabet[k++];
            }
        }
    }
}

// Function to find the position of a letter in the matrix
void find_position(char matrix[MATRIX_SIZE][MATRIX_SIZE], char letter, int *row, int *col) {
    int i, j;

    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a digraph
void encrypt(char matrix[MATRIX_SIZE][MATRIX_SIZE], char plaintext[], char ciphertext[]) {
    int i, len, row1, col1, row2, col2;
    char ch1, ch2;

    len = strlen(plaintext);
    i = 0;

    while (i < len) {
        ch1 = plaintext[i++];
        ch2 = (i < len) ? plaintext[i++] : 'X'; // If plaintext length is odd, append 'X' to make it even

        // If both letters are the same, insert an 'X' between them (playfair rule)
        if (ch1 == ch2) {
            ch2 = 'X';
            i--; // Adjust index to process the same character again
        }

        // Find positions of digraph in the matrix
        find_position(matrix, ch1, &row1, &col1);
        find_position(matrix, ch2, &row2, &col2);

        // Encrypt according to Playfair rules
        if (row1 == row2) { // Same row
            ciphertext[i - 2] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            ciphertext[i - 1] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
        } else if (col1 == col2) { // Same column
            ciphertext[i - 2] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            ciphertext[i - 1] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
        } else { // Rectangle rule
            ciphertext[i - 2] = matrix[row1][col2];
            ciphertext[i - 1] = matrix[row2][col1];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char key[100], plaintext[1000], ciphertext[1000];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];

    // Get the key from the user
    printf("Enter the key for the Playfair cipher (no spaces, uppercase only): ");
    scanf("%s", key);

    // Prepare the key and fill the matrix
    prepare_key(key, matrix);

    // Get plaintext input from the user
    printf("Enter plaintext to encrypt (uppercase only, no spaces): ");
    scanf("%s", plaintext);

    // Encrypt the plaintext using Playfair cipher
    encrypt(matrix, plaintext, ciphertext);

    // Output the encrypted ciphertext
    printf("Encrypted ciphertext: %s\n", ciphertext);

    return 0;
}

