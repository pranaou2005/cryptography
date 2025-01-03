#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h

void print_hex(const char *label, const unsigned char *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void handle_errors() {
    fprintf(stderr, "An error occurred\n");
    exit(EXIT_FAILURE);
}

void des_encrypt_ecb(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext) {
    DES_cblock key_block;
    DES_key_schedule key_schedule;

    memcpy(key_block, key, 8);
    DES_set_key_unchecked(&key_block, &key_schedule);

    int num_blocks = plaintext_len / 8;
    for (int i = 0; i < num_blocks; i++) {
        DES_ecb_encrypt((DES_cblock *)(plaintext + i * 8), (DES_cblock *)(ciphertext + i * 8), &key_schedule, DES_ENCRYPT);
    }
}

void des_decrypt_ecb(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *plaintext) {
    DES_cblock key_block;
    DES_key_schedule key_schedule;

    memcpy(key_block, key, 8);
    DES_set_key_unchecked(&key_block, &key_schedule);

    int num_blocks = ciphertext_len / 8;
    for (int i = 0; i < num_blocks; i++) {
        DES_ecb_encrypt((DES_cblock *)(ciphertext + i * 8), (DES_cblock *)(plaintext + i * 8), &key_schedule, DES_DECRYPT);
    }
}

void des_encrypt_cbc(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext) {
    DES_cblock key_block, iv_block;
    DES_key_schedule key_schedule;

    memcpy(key_block, key, 8);
    DES_set_key_unchecked(&key_block, &key_schedule);
    memcpy(iv_block, iv, 8);

    DES_ncbc_encrypt(plaintext, ciphertext, plaintext_len, &key_schedule, &iv_block, DES_ENCRYPT);
}

void des_decrypt_cbc(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext) {
    DES_cblock key_block, iv_block;
    DES_key_schedule key_schedule;

    memcpy(key_block, key, 8);
    DES_set_key_unchecked(&key_block, &key_schedule);
    memcpy(iv_block, iv, 8);

    DES_ncbc_encrypt(ciphertext, plaintext, ciphertext_len, &key_schedule, &iv_block, DES_DECRYPT);
}

int main() {
    // Example plaintext
    const unsigned char plaintext[] = "This is a test message for DES encryption.";
    int plaintext_len = strlen((const char *)plaintext);

    // DES key (8 bytes)
    unsigned char key[8];
    memcpy(key, "12345678", 8);

    // Initialization vector (8 bytes) for CBC mode
    unsigned char iv[8];
    memcpy(iv, "87654321", 8);

    // Buffers for ciphertext and decrypted text
    unsigned char ciphertext_ecb[128];
    unsigned char decrypted_ecb[128];
    unsigned char ciphertext_cbc[128];
    unsigned char decrypted_cbc[128];

    // ECB Mode Encryption
    des_encrypt_ecb(plaintext, plaintext_len, key, ciphertext_ecb);
    print_hex("ECB Ciphertext", ciphertext_ecb, plaintext_len);

    // ECB Mode Decryption
    des_decrypt_ecb(ciphertext_ecb, plaintext_len, key, decrypted_ecb);
    print_hex("ECB Decrypted", decrypted_ecb, plaintext_len);

    // CBC Mode Encryption
    des_encrypt_cbc(plaintext, plaintext_len, key, iv, ciphertext_cbc);
    print_hex("CBC Ciphertext", ciphertext_cbc, plaintext_len);

    // Simulate an error in the transmitted ciphertext for CBC mode
    ciphertext_cbc[8] ^= 0xFF;  // Introduce an error in the second block

    // CBC Mode Decryption
    des_decrypt_cbc(ciphertext_cbc, plaintext_len, key, iv, decrypted_cbc);
    print_hex("CBC Decrypted (with error)", decrypted_cbc, plaintext_len);

    return 0;
}
