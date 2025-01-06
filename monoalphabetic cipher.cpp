#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt_decrypt(char text[], char key[], int mode) {
    char map[26];
    for (int i = 0; i < 26; i++)
        map[key[i] - 'A'] = mode ? 'A' + i : key[i];

    for (int i = 0; text[i]; i++)
        if (isalpha(text[i]))
            text[i] = map[toupper(text[i]) - 'A'] - (isupper(text[i]) ? 0 : 'A' - 'a');
}
int main() {
    char key[27], text[100];
    printf("Enter key (26 letters): ");
    scanf("%s", key);
    getchar(); // Consume leftover newline
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
	  
	encrypt_decrypt(text, key, 0); // Encrypt
    printf("DECRYPT : %s", text);
    
    encrypt_decrypt(text, key, 1); // Decrypt
    printf("ENCRYPT: %s", text);
    return 0;
}

