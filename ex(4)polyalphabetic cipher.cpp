#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereCipher(char text[], char key[], int mode) {
    int textLen = strlen(text), keyLen = strlen(key);
    for (int i = 0, j = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int shift = (toupper(key[j % keyLen]) - 'A') * (mode ? -1 : 1);
            text[i] = base + (text[i] - base + shift + 26) % 26; 
            j++; 
        }
    }
}
int main() {
    char text[100], key[100];
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    printf("Enter key: ");
    scanf("%s", key);

    // Encryption
    vigenereCipher(text, key, 0);
    printf("Ciphertext: %s\n", text);

    // Decryption
    vigenereCipher(text, key, 1);
    printf("Decrypted text: %s\n", text);

    return 0;
}

