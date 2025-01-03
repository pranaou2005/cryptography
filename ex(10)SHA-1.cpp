#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define MAX_LENGTH 256

char playfair_matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void find_position(char ch, int* row, int* col) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (playfair_matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void prepare_message(const char* message, char* prepared_message) {
    int index = 0;
    for (int i = 0; i < strlen(message); i++) {
        char ch = toupper(message[i]);
        if (isalpha(ch)) {
            if (ch == 'J') ch = 'I';
            prepared_message[index++] = ch;
        }
    }
    for (int i = 0; i < index; i += 2) {
        if (i + 1 >= index) {
            prepared_message[index++] = 'X'; 
        } else if (prepared_message[i] == prepared_message[i + 1]) {
            for (int j = index; j > i + 1; j--) {
                prepared_message[j] = prepared_message[j - 1];
            }
            prepared_message[i + 1] = 'X';
            index++;
        }
    }
    prepared_message[index] = '\0';
}
void encrypt_pair(char* pair, char* encrypted_pair) {
    int row1, col1, row2, col2;
    find_position(pair[0], &row1, &col1);
    find_position(pair[1], &row2, &col2);

    if (row1 == row2) {
        encrypted_pair[0] = playfair_matrix[row1][(col1 + 1) % SIZE];
        encrypted_pair[1] = playfair_matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        encrypted_pair[0] = playfair_matrix[(row1 + 1) % SIZE][col1];
        encrypted_pair[1] = playfair_matrix[(row2 + 1) % SIZE][col2];
    } else {
        encrypted_pair[0] = playfair_matrix[row1][col2];
        encrypted_pair[1] = playfair_matrix[row2][col1];
    }
}

// Function to encrypt the message using Playfair cipher
void encrypt_message(const char* message, char* encrypted_message) {
    char prepared_message[MAX_LENGTH];
    prepare_message(message, prepared_message);

    int length = strlen(prepared_message);
    for (int i = 0; i < length; i += 2) {
        char pair[2] = {prepared_message[i], prepared_message[i + 1]};
        char encrypted_pair[2];
        encrypt_pair(pair, encrypted_pair);
        encrypted_message[i] = encrypted_pair[0];
        encrypted_message[i + 1] = encrypted_pair[1];
    }
    encrypted_message[length] = '\0';
}

int main() {
    const char* message = "Must see you over Cadogan West. Coming at once.";
    char encrypted_message[MAX_LENGTH];

    encrypt_message(message, encrypted_message);
    printf("Encrypted message: %s\n", encrypted_message);

    return 0;
}