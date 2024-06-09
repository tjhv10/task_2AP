#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num;
    int total_counter = 0;

    // Start timing
    clock_t start_time = clock();

    // Read numbers from stdin until end of file
    while (scanf("%d", &num) != EOF) {
        if (isPrime(num)) {
            total_counter++;
        }
    }

    // End timing
    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("%d total primes.\n", total_counter);
    printf("Time taken: %f seconds.\n", time_spent);

    return 0;
}
