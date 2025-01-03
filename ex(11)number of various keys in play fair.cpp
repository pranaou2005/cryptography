#include <stdio.h>
#include <math.h>

#define FACTORIAL_LIMIT 25
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
double compute_power_of_two(unsigned long long num) {
    return log2(num);
}

int main() {
    unsigned long long total_keys = factorial(FACTORIAL_LIMIT);
    double power_of_two = compute_power_of_two(total_keys);

    printf("Total possible keys (approx. power of 2): 2^%.0f\n", power_of_two);
    
    return 0;
}
