#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 24

typedef unsigned char BYTE;

void print_hex(const char *label, const BYTE *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void xor_blocks(BYTE *out, const BYTE *in1, const BYTE *in2) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}

// Simple DES encryption/decryption function placeholder
void des_encrypt_block(const BYTE *in, BYTE *out, const BYTE *key) {
    // For simplicity, this is a placeholder for the actual DES encryption
    // A real implementation would be much more complex
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = in[i] ^ key[i];
    }
}

void des_decrypt_block(const BYTE *in, BYTE *out, const BYTE *key) {
    // For simplicity, this is a placeholder for the actual DES decryption
    // A real implementation would be much more complex
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = in[i] ^ key[i];
    }
}

void triple_des_encrypt_block(const BYTE *in, BYTE *out, const BYTE *key) {
    BYTE temp[BLOCK_SIZE];
    des_encrypt_block(in, temp, key);                // Encrypt with K1
    des_decrypt_block(temp, out, key + BLOCK_SIZE);  // Decrypt with K2
    des_encrypt_block(out, temp, key + 2 * BLOCK_SIZE); // Encrypt with K3
    memcpy(out, temp, BLOCK_SIZE);
}

void triple_des_decrypt_block(const BYTE *in, BYTE *out, const BYTE *key) {
    BYTE temp[BLOCK_SIZE];
    des_decrypt_block(in, temp, key + 2 * BLOCK_SIZE); // Decrypt with K3
    des_encrypt_block(temp, out, key + BLOCK_SIZE);    // Encrypt with K2
    des_decrypt_block(out, temp, key);                 // Decrypt with K1
    memcpy(out, temp, BLOCK_SIZE);
}

void cbc_encrypt(const BYTE *plaintext, int plaintext_len, const BYTE *key, const BYTE *iv, BYTE *ciphertext) {
    BYTE buffer[BLOCK_SIZE];
    BYTE prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        xor_blocks(buffer, plaintext + i, prev_block);
        triple_des_encrypt_block(buffer, ciphertext + i, key);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void cbc_decrypt(const BYTE *ciphertext, int ciphertext_len, const BYTE *key, const BYTE *iv, BYTE *plaintext) {
    BYTE buffer[BLOCK_SIZE];
    BYTE prev_block[BLOCK_SIZE];
    BYTE curr_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        memcpy(curr_block, ciphertext + i, BLOCK_SIZE);
        triple_des_decrypt_block(ciphertext + i, buffer, key);
        xor_blocks(plaintext + i, buffer, prev_block);
        memcpy(prev_block, curr_block, BLOCK_SIZE);
    }
}

int main() {
    const BYTE plaintext[] = "This is a test message for 3DES encryption in CBC mode.";
    int plaintext_len = strlen((const char *)plaintext);
    BYTE padded_plaintext[64];
    memcpy(padded_plaintext, plaintext, plaintext_len);
    int padded_len = ((plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    for (int i = plaintext_len; i < padded_len; i++) {
        padded_plaintext[i] = 0;
    }

    // 3DES key (24 bytes)
   // 3DES key (24 bytes)
BYTE key[KEY_SIZE + 1] = "0123456789abcdef01234567";

// Initialization vector (8 bytes)
BYTE iv[BLOCK_SIZE + 1] = "12345678";


    // Buffers for ciphertext and decrypted text
    BYTE ciphertext[64];
    BYTE decrypted[64];

    // Encrypt the plaintext
    cbc_encrypt(padded_plaintext, padded_len, key, iv, ciphertext);

    // Print the plaintext and ciphertext
    print_hex("Plaintext", padded_plaintext, padded_len);
    print_hex("Ciphertext", ciphertext, padded_len);

    // Decrypt the ciphertext
    cbc_decrypt(ciphertext, padded_len, key, iv, decrypted);
    print_hex("Decrypted", decrypted, padded_len);

    return 0;
}
