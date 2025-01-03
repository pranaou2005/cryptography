#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Simulated RSA functions
uint32_t mod_exp(uint32_t base, uint32_t exp, uint32_t mod) {
    uint32_t result = 1;
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

// RSA Sign function (simplified for demonstration)
uint32_t rsa_sign(uint32_t private_key, uint32_t message, uint32_t n) {
    return mod_exp(message, private_key, n); // Simple modular exponentiation
}

// Simulated DSA functions
#define P 0xF9D1B6D6  // A large prime number (p)
#define Q 0xC63B7D89  // A prime divisor (q)
#define G 0x11235813  // A generator (g)

// Function to generate random k for DSA
uint32_t generate_random_k(uint32_t max) {
    return rand() % (max - 1) + 1;  // k must be between 1 and Q-1
}

// Function to compute modular exponentiation for DSA
uint32_t mod_exp_dsa(uint32_t a, uint32_t b, uint32_t m) {
    uint32_t result = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        b = b >> 1;
        a = (a * a) % m;
    }
    return result;
}

// Function to sign a message using DSA
void dsa_sign(uint32_t private_key, uint32_t message, uint32_t *r, uint32_t *s) {
    uint32_t k = generate_random_k(Q);  // Random k for each signature
    uint32_t hash = message;            // Use message as hash for simplicity

    *r = mod_exp_dsa(G, k, P) % Q;     // r = (G^k) mod P % Q
    *s = (mod_exp_dsa(k, Q-2, Q) * (hash + private_key * *r)) % Q;  // s = (k^-1 * (hash + private_key * r)) mod Q
}

// Function to verify the RSA signature
int verify_rsa_signature(uint32_t signature, uint32_t public_key, uint32_t message, uint32_t n) {
    uint32_t expected_signature = mod_exp(message, public_key, n);
    return signature == expected_signature; // If signature matches, it's valid
}

// Function to verify DSA signature
int verify_dsa_signature(uint32_t public_key, uint32_t message, uint32_t r, uint32_t s) {
    uint32_t hash = message;  // Simplified hash
    uint32_t w = mod_exp_dsa(s, Q - 2, Q);  // w = s^-1 mod Q
    uint32_t u1 = (hash * w) % Q;  // u1 = (message * w) mod Q
    uint32_t u2 = (r * w) % Q;    // u2 = (r * w) mod Q
    uint32_t v = (mod_exp_dsa(G, u1, P) * mod_exp_dsa(public_key, u2, P)) % P % Q;

    return v == r;  // If v == r, the signature is valid
}

int main() {
    srand(time(NULL));  // Seed random number generator
    
    uint32_t rsa_private_key = 0xA1B2C3D4;  // Example RSA private key
    uint32_t rsa_public_key = 0xE5F6A7B8;   // A valid RSA public key (changed from invalid "0xE5F6G7H8")
    uint32_t rsa_n = 0xDEADBEEF;            // Example modulus n
    
    // Message to be signed
    uint32_t message = 0xDEADBEEF;

    // RSA signing (same signature for each run)
    uint32_t rsa_signature1 = rsa_sign(rsa_private_key, message, rsa_n);
    uint32_t rsa_signature2 = rsa_sign(rsa_private_key, message, rsa_n);

    printf("RSA Signature 1: 0x%X\n", rsa_signature1);
    printf("RSA Signature 2: 0x%X\n", rsa_signature2);
    printf("RSA Signatures Match: %s\n", (rsa_signature1 == rsa_signature2) ? "Yes" : "No");

    // DSA signing (different signature for each run)
    uint32_t dsa_private_key = 0xA1B2C3D4;  // Example DSA private key
    uint32_t dsa_public_key = mod_exp_dsa(G, dsa_private_key, P);  // DSA public key
    
    uint32_t r1, s1, r2, s2;
    dsa_sign(dsa_private_key, message, &r1, &s1);
    dsa_sign(dsa_private_key, message, &r2, &s2);

    printf("DSA Signature 1: (r = 0x%X, s = 0x%X)\n", r1, s1);
    printf("DSA Signature 2: (r = 0x%X, s = 0x%X)\n", r2, s2);
    printf("DSA Signatures Match: %s\n", (r1 == r2 && s1 == s2) ? "Yes" : "No");

    return 0;
}

