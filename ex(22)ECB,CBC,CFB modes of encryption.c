#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 16  // AES block size in bytes (128 bits)

void xor_blocks(unsigned char *block, unsigned char *iv) {
    int i;
    for (i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= iv[i];
    }
}

void pad_data(unsigned char *data, int *data_len) {
    int padding_len = BLOCK_SIZE - (*data_len % BLOCK_SIZE);
    data[*data_len] = 0x80; // Padding starts with 0x80 (binary 10000000)
    int i;
    for (i = *data_len + 1; i < *data_len + padding_len; i++) {
        data[i] = 0x00; // Pad with zero bytes
    }
    *data_len += padding_len;
}

// AES Encryption (For demonstration, replace with actual AES function in real implementation)
void aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key) {
    int i;
    // Dummy AES encryption for illustration purposes
    for (i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i]; // Simple XOR encryption (not AES)
    }
}

// ECB Mode Encryption
void ecb_encrypt(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key, int data_len) {
    unsigned char block[BLOCK_SIZE];
    int i;
    for (i = 0; i < data_len; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);
        aes_encrypt(block, ciphertext + i, key);
    }
}

// CBC Mode Encryption
void cbc_encrypt(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key, unsigned char *iv, int data_len) {
    unsigned char block[BLOCK_SIZE];
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    int i;
    for (i = 0; i < data_len; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);
        xor_blocks(block, prev_block);
        aes_encrypt(block, ciphertext + i, key);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

// CFB Mode Encryption
void cfb_encrypt(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key, unsigned char *iv, int data_len) {
    unsigned char block[BLOCK_SIZE];
    unsigned char temp[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);

    int i, j;
    for (i = 0; i < data_len; i += BLOCK_SIZE) {
        aes_encrypt(temp, block, key);
        for (j = 0; j < BLOCK_SIZE && (i + j) < data_len; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ block[j];
        }
        memcpy(temp, block, BLOCK_SIZE);
    }
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x00};  // AES Key (dummy for illustration)
    unsigned char iv[BLOCK_SIZE] = {0x00};   // Initialization vector (for CBC/CFB)
    unsigned char plaintext[64] = "This is a test message that needs to be encrypted!";
    unsigned char ciphertext[64];
    int data_len = strlen((char *)plaintext);
    int i;
    
    // Padding the plaintext to a multiple of BLOCK_SIZE
    pad_data(plaintext, &data_len);

    printf("Plaintext: %s\n", plaintext);

    // ECB Encryption
    ecb_encrypt(plaintext, ciphertext, key, data_len);
    printf("Ciphertext (ECB): ");
    for ( i = 0; i < data_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // CBC Encryption
    cbc_encrypt(plaintext, ciphertext, key, iv, data_len);
    printf("Ciphertext (CBC): ");
    for ( i = 0; i < data_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // CFB Encryption
    cfb_encrypt(plaintext, ciphertext, key, iv, data_len);
    printf("Ciphertext (CFB): ");
    for ( i = 0; i < data_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

