#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute (base^exp) % mod using modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long p = 23;   // A small prime number (modulus)
    long long g = 5;    // A small base number (generator)
    
    // Alice's private key
    long long a = 6;
    
    // Bob's private key
    long long b = 15;
    
    // Alice calculates A = g^a mod p
    long long A = mod_exp(g, a, p);
    printf("Alice's public value A = %lld\n", A);
    
    // Bob calculates B = g^b mod p
    long long B = mod_exp(g, b, p);
    printf("Bob's public value B = %lld\n", B);
    
    // Alice computes shared secret key using Bob's public value
    long long secret_Alice = mod_exp(B, a, p);
    printf("Alice's shared secret: %lld\n", secret_Alice);
    
    // Bob computes shared secret key using Alice's public value
    long long secret_Bob = mod_exp(A, b, p);
    printf("Bob's shared secret: %lld\n", secret_Bob);
    
    // Both secrets should match
    if (secret_Alice == secret_Bob) {
        printf("Shared secret is successfully agreed upon: %lld\n", secret_Alice);
    } else {
        printf("Failed to agree on the same shared secret.\n");
    }

    return 0;
}

