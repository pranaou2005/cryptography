#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MX 5

void playfair(char ch1, char ch2, char key[MX][MX]) {
    int i, j, w, x, y, z;
    FILE *out;

    // Open file for appending the cipher text
    if ((out = fopen("cipher.txt", "a+")) == NULL) {
        printf("File Corrupted.");
        return;
    }

    // Find the positions of the two characters in the key matrix
    for (i = 0; i < MX; i++) {
        for (j = 0; j < MX; j++) {
            if (ch1 == key[i][j]) {
                w = i;
                x = j;
            } else if (ch2 == key[i][j]) {
                y = i;
                z = j;
            }
        }
    }

    // Encrypt according to Playfair rules
    if (w == y) { // Same row
        x = (x + 1) % MX;
        z = (z + 1) % MX;
    } else if (x == z) { // Same column
        w = (w + 1) % MX;
        y = (y + 1) % MX;
    } else { // Rectangle swap
        int temp = x;
        x = z;
        z = temp;
    }

    printf("%c%c", key[w][x], key[y][z]);
    fprintf(out, "%c%c", key[w][x], key[y][z]);
    fclose(out);
}

int main() {
    int i, j, k = 0, l, m = 0, n;
    char key[MX][MX], keyminus[25], keystr[10], str[25] = {0};
    char alpa[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                     'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    printf("\nEnter key: ");
    gets(keystr);
    printf("\nEnter the plain text: ");
    gets(str);

    n = strlen(keystr);

    // Convert the key to uppercase and replace 'J' with 'I'
    for (i = 0; i < n; i++) {
        if (keystr[i] == 'j') keystr[i] = 'i';
        else if (keystr[i] == 'J') keystr[i] = 'I';
        keystr[i] = toupper(keystr[i]);
    }

    // Convert plaintext to uppercase and replace 'J' with 'I'
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == 'j') str[i] = 'i';
        else if (str[i] == 'J') str[i] = 'I';
        str[i] = toupper(str[i]);
    }

    // Remove characters already in the key from the alphabet
    j = 0;
    for (i = 0; i < 26; i++) {
        for (k = 0; k < n; k++) {
            if (keystr[k] == alpa[i]) break;
            if (alpa[i] == 'J') break;
        }
        if (k == n) {
            keyminus[j] = alpa[i];
            j++;
        }
    }

    // Construct the key matrix
    k = 0;
    for (i = 0; i < MX; i++) {
        for (j = 0; j < MX; j++) {
            if (k < n) {
                key[i][j] = keystr[k];
                k++;
            } else {
                key[i][j] = keyminus[m];
                m++;
            }
            printf("%c ", key[i][j]);
        }
        printf("\n");
    }

    printf("\n\nEntered text: %s\nCipher Text: ", str);

    // Encrypt the plaintext
    for (i = 0; i < strlen(str); i++) {a
        if (str[i] == 'J') str[i] = 'I';
        if (str[i + 1] == '\0') {
            playfair(str[i], 'X', key); // Append 'X' if there's an odd number of characters
        } else {
            if (str[i] == str[i + 1]) {
                playfair(str[i], 'X', key); // Add 'X' if two consecutive characters are the same
            } else {
                playfair(str[i], str[i + 1], key);
                i++; // Skip the next character
            }
        }
    }

    return 0;
}

