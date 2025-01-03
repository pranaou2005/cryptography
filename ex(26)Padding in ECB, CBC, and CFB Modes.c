#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Block size in bytes (e.g., AES uses 16 bytes)
#define BLOCK_SIZE 16

// Function to perform XOR operation on two blocks
void xor_blocks(unsigned char *block1, unsigned char *block2, unsigned char *result) {
    int i;
	for (i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

// Electronic Codebook (ECB) mode
void ecb_mode(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key) {
    // Encrypt each block independently
    int i;
	for (i = 0; i < strlen(plaintext); i += BLOCK_SIZE) {
        // Perform encryption (e.g., AES_encrypt)
        // For simplicity, assume a simple XOR with the key
        xor_blocks(plaintext + i, key, ciphertext + i);
    }
}

// Cipher Block Chaini
void cbc_mode(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key, unsigned char *iv) {
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    // Encrypt each block
    int i;
	for (i = 0; i < strlen(plaintext); i += BLOCK_SIZE) {
        // XOR plaintext with previous block (or IV)
        unsigned char temp_block[BLOCK_SIZE];
        xor_blocks(plaintext + i, prev_block, temp_block);

        // Perform encryption (e.g., AES_encrypt)
        // For simplicity, assume a simple XOR with the key
        xor_blocks(temp_block, key, ciphertext + i);

        // Update previous block
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

// Counter (CTR) mode
void ctr_mode(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key, unsigned char *nonce) {
    unsigned char counter[BLOCK_SIZE];
    memcpy(counter, nonce, BLOCK_SIZE);

    // Encrypt each block
    int i;
	for (i = 0; i < strlen(plaintext); i += BLOCK_SIZE) {
        // Increment counter
        int j;
		for (j = BLOCK_SIZE - 1; j >= 0; j--) {
            if (counter[j] == 255) {
                counter[j] = 0;
            } else {
                counter[j]++;
                break;
            }
        }

        // Perform encryption (e.g., AES_encrypt)
        // For simplicity, assume a simple XOR with the key and counter
        unsigned char temp_block[BLOCK_SIZE];
        xor_blocks(counter, key, temp_block);
        xor_blocks(plaintext + i, temp_block, ciphertext + i);
    }
}

int main() {
    unsigned char plaintext[] = "This is a secret message";
unsigned char key[] = "my_secret_key";
    unsigned char iv[] = "initialization_vector";
    unsigned char nonce[] = "counter_nonce";

    unsigned char ciphertext[strlen(plaintext)];

    printf("ECB mode:\n");
    ecb_mode(plaintext, ciphertext, key);
    printf("%s\n", ciphertext);

    printf("CBC mode:\n");
    cbc_mode(plaintext, ciphertext, key, iv);
    printf("%s\n", ciphertext);

    printf("CTR mode:\n");
    ctr_mode(plaintext, ciphertext, key, nonce);
    printf("%s\n", ciphertext);

    return 0;
}


