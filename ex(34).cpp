#include <iostream>
#include <cstring> // Include the <cstring> header for strlen function
using namespace std;

void affine_caesar_encrypt(int a, int b, char plaintext[], char ciphertext[]) {
    int i;
    int len = strlen(plaintext); // Use strlen from <cstring>

    // Encrypt each character in the plaintext
    for (i = 0; i < len; i++) {
        char p = plaintext[i];

        if (isalpha(p)) {
            int offset = isupper(p) ? 'A' : 'a';
            ciphertext[i] = (char)(((a * (p - offset) + b) % 26 + 26) % 26 + offset);
        } else {
            ciphertext[i] = p; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[] = "HelloWorld";
    char ciphertext[1000];
    int a, b;

    cout << "Enter values of a and b for affine Caesar cipher (a must be coprime with 26):\n";
    cin >> a >> b;

    // Check if a is coprime with 26
    // (You might want to implement the gcd function as shown earlier)

    // Encrypt the plaintext using the affine Caesar cipher
    affine_caesar_encrypt(a, b, plaintext, ciphertext);

    // Output the encrypted ciphertext
    cout << "Encrypted ciphertext: " << ciphertext << endl;

    return 0;
}

