#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

const double english_frequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.316, 9.056, 
    2.758, 0.978, 2.560, 0.150, 1.929, 0.074
};

typedef struct {
    char letter;
    double frequency;
} Frequency;

void compute_frequency(const char *text, Frequency freq[ALPHABET_SIZE]) {
    int counts[ALPHABET_SIZE] = {0};
    int total_letters = 0;
    int i;
    
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char ch = tolower(text[i]) - 'a';
            counts[ch]++;
            total_letters++;
        }
    }

    for (i = 0; i < ALPHABET_SIZE; i++) {
        freq[i].letter = 'a' + i;
        freq[i].frequency = (total_letters > 0) ? (counts[i] / (double)total_letters) * 100.0 : 0.0;
    }
}

int compare_frequency(const void *a, const void *b) {
    Frequency *freq1 = (Frequency *)a;
    Frequency *freq2 = (Frequency *)b;
    return (freq2->frequency > freq1->frequency) - (freq2->frequency < freq1->frequency);
}

void generate_plaintext(const char *ciphertext, const Frequency cipher_freq[ALPHABET_SIZE], const Frequency english_freq[ALPHABET_SIZE], char *plaintext) {
    char mapping[ALPHABET_SIZE];
    int i;

    for (i = 0; i < ALPHABET_SIZE; i++) {
        mapping[cipher_freq[i].letter - 'a'] = english_freq[i].letter;
    }

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = tolower(ciphertext[i]) - 'a';
            plaintext[i] = isupper(ciphertext[i]) ? toupper(mapping[ch]) : mapping[ch];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[256];
    char plaintext[256];
    Frequency cipher_freq[ALPHABET_SIZE];
    Frequency sorted_english_freq[ALPHABET_SIZE];
    int i, j, top_n;

    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    size_t length = strlen(ciphertext);
    if (length > 0 && ciphertext[length - 1] == '\n') {
        ciphertext[length - 1] = '\0';
    }

    printf("Enter the number of plaintexts to generate: ");
    scanf("%d", &top_n);

    // Initialize English frequencies with corresponding letters
    for (i = 0; i < ALPHABET_SIZE; i++) {
        sorted_english_freq[i].letter = 'a' + i;
        sorted_english_freq[i].frequency = english_frequencies[i];
    }

    // Sort English frequencies in descending order
    qsort(sorted_english_freq, ALPHABET_SIZE, sizeof(Frequency), compare_frequency);

    // Compute ciphertext frequencies
    compute_frequency(ciphertext, cipher_freq);

    // Sort ciphertext frequencies in descending order
    qsort(cipher_freq, ALPHABET_SIZE, sizeof(Frequency), compare_frequency);

    // Generate and display the top N plaintexts
    printf("\nPossible plaintexts (frequency analysis):\n");
    for (i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        // Adjust English frequency order for each permutation
        for (j = 0; j < ALPHABET_SIZE; j++) {
            sorted_english_freq[j].letter = 'a' + ((j + i) % ALPHABET_SIZE);
        }

        generate_plaintext(ciphertext, cipher_freq, sorted_english_freq, plaintext);
        printf("%d. %s\n", i + 1, plaintext);
    }

    return 0;
}

