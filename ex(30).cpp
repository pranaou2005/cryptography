#include <stdio.h>
#include <ctype.h>

// Function to encrypt or decrypt a message using Caesar cipher
void caesarCipher(char message[], int key, char mode) {
    char ch;
    int i;

    // Ensure key is within the range 1 to 25
    key = key % 26;
    if (key <= 0) {
        key += 26;
    }

    // Iterate through each character in the message
    for (i = 0; message[i] != '\0'; ++i) {
        ch = message[i];

        if (isalpha(ch)) {
            // Determine whether to encrypt or decrypt based on mode ('e' or 'd')
            if (mode == 'e') {
                // Encryption
                if (isupper(ch)) {
                    ch = 'A' + (ch - 'A' + key) % 26;
                } else {
                    ch = 'a' + (ch - 'a' + key) % 26;
                }
            } else if (mode == 'd') {
                // Decryption
                if (isupper(ch)) {
                    ch = 'A' + (ch - 'A' - key + 26) % 26;
                } else {
                    ch = 'a' + (ch - 'a' - key + 26) % 26;
                }
            }
        }
        
        // Print the encrypted or decrypted character
        printf("%c", ch);
    }
}

int main() {
    char message[100];
    int key, choice;

    // Prompt user for message input
    printf("Enter a message to encrypt or decrypt: ");
    fgets(message, sizeof(message), stdin);

    // Prompt user for key input
    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    // Prompt user for choice (encrypt 'e' or decrypt 'd')
    printf("Enter 'e' to encrypt or 'd' to decrypt: ");
    scanf(" %c", &choice);

    // Validate the choice
    if (choice == 'e' || choice == 'd') {
        // Encrypt or decrypt the message based on user's choice
        printf("Result: ");
        caesarCipher(message, key, choice);
        printf("\n");
    } else {
        printf("Invalid choice. Please enter 'e' or 'd'.\n");
    }

    return 0;
}

