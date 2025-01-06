#include <stdio.h>
#include <string.h>
#include <ctype.h>

void monoalphabeticCipher(const char *message, char *encryptedMessage, const char *key) {
    for (int i = 0; message[i] != '\0'; ++i) {
        if (isalpha(message[i])) {
            int index = toupper(message[i]) - 'A';
            encryptedMessage[i] = isupper(message[i]) ? key[index] : tolower(key[index]);
        } else {
            encryptedMessage[i] = message[i];
        }
    }
    encryptedMessage[strlen(message)] = '\0';
}

int main() {
    char message[100];
    char encryptedMessage[100];
    char key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    monoalphabeticCipher(message, encryptedMessage, key);

    printf("Encrypted message: %s\n", encryptedMessage);

    return 0;
}
