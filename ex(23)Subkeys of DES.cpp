#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DES_KEY_SIZE 64
#define DES_SUBKEY_SIZE 48
#define PC1_SIZE 56
#define PC2_SIZE 48
#define NUM_SUBKEYS 16
int PC1[PC1_SIZE] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};
int PC2[PC2_SIZE] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
int LEFT_SHIFTS[NUM_SUBKEYS] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};
void left_circular_shift(uint8_t *half_key, int shifts) {
    uint8_t temp[28];
    memcpy(temp, half_key, 28);
    for (int i = 0; i < 28; i++) {
        half_key[i] = temp[(i + shifts) % 28];
    }
}
void generate_subkeys(uint8_t key[DES_KEY_SIZE], uint8_t subkeys[NUM_SUBKEYS][DES_SUBKEY_SIZE]) {
    uint8_t permuted_key[PC1_SIZE];
    uint8_t left_half[28], right_half[28];
    for (int i = 0; i < PC1_SIZE; i++) {
        permuted_key[i] = key[PC1[i] - 1];
    }
    memcpy(left_half, permuted_key, 28);
    memcpy(right_half, permuted_key + 28, 28);
    for (int round = 0; round < NUM_SUBKEYS; round++) {
        left_circular_shift(left_half, LEFT_SHIFTS[round]);
        left_circular_shift(right_half, LEFT_SHIFTS[round]);
        uint8_t combined_key[56];
        memcpy(combined_key, left_half, 28);
        memcpy(combined_key + 28, right_half, 28);

        for (int i = 0; i < PC2_SIZE; i++) {
            subkeys[round][i] = combined_key[PC2[i] - 1];
        }
    }
}
void print_subkeys(uint8_t subkeys[NUM_SUBKEYS][DES_SUBKEY_SIZE]) {
    for (int i = 0; i < NUM_SUBKEYS; i++) {
        printf("Subkey %2d: ", i + 1);
        for (int j = 0; j < DES_SUBKEY_SIZE; j++) {
            printf("%d", subkeys[i][j]);
        }
        printf("\n");
    }
}
int main() {
    uint8_t key[DES_KEY_SIZE] = {
        0, 1, 1, 0, 0, 0, 1, 1,  
        1, 0, 0, 1, 0, 1, 1, 0, 
        0, 1, 1, 0, 1, 1, 0, 1,  
        1, 0, 0, 0, 0, 0, 1, 0,  
        1, 1, 1, 0, 1, 1, 0, 1, 
        0, 0, 1, 0, 1, 1, 1, 1,  
        1, 0, 1, 1, 1, 1, 0, 0,  
        1, 0, 1, 1, 0, 1, 1, 1   
    };
    uint8_t subkeys[NUM_SUBKEYS][DES_SUBKEY_SIZE];
    generate_subkeys(key, subkeys);
    print_subkeys(subkeys);

    return 0;
}
