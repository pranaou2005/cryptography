#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    
    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;
    return x1;
}

void generate_keys(long long *n, long long *e, long long *d, long long p, long long q) {
    *n = p * q;  // modulus
    long long phi = (p - 1) * (q - 1);  // Euler's totient function

    // Choose e such that gcd(e, phi) = 1
    *e = 65537;  // Common choice for e
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }

    // Calculate d such that d * e = 1 (mod phi)
    *d = mod_inverse(*e, phi);
}

int main() {
    srand(time(NULL));

    // Original prime numbers (Bob's initial key pair)
    long long p = 61, q = 53;
    long long n, e, d;

    generate_keys(&n, &e, &d, p, q);

    printf("Original Public Key: (e = %lld, n = %lld)\n", e, n);
    printf("Original Private Key: (d = %lld)\n", d);

    // Simulating the leak of Bob's private key
    printf("\nBob's private key is leaked!\n");

    // Bob tries to generate a new key pair with the same modulus (unsafe)
    long long new_e, new_d;
    generate_keys(&n, &new_e, &new_d, p, q);

    printf("\nBob's new public key (e = %lld, n = %lld)\n", new_e, n);
    printf("Bob's new private key (d = %lld)\n", new_d);

    // Now, anyone with the leaked private key can decrypt messages.
    printf("\nLeaked private key allows an attacker to decrypt messages intended for Bob.\n");

    // Simulate encryption and decryption with the original keys
    long long message = 12345;  // Message to encrypt
    long long ciphertext = mod_exp(message, e, n);
    long long decrypted_message = mod_exp(ciphertext, d, n);
    printf("\nOriginal encryption/decryption:\n");
    printf("Encrypted Message: %lld\n", ciphertext);
    printf("Decrypted Message: %lld\n", decrypted_message);

    // Simulate decryption with the leaked key (new private key)
    long long attacker_decrypted_message = mod_exp(ciphertext, new_d, n);
    printf("\nAttacker decrypting message with leaked private key:\n");
    printf("Decrypted Message (Leaked Key): %lld\n", attacker_decrypted_message);

    return 0;
}

