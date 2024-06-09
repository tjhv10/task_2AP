#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/resource.h>

#define MAX_THREADS 8
#define STACK_SIZE (256 * 1024) // 256 KB per thread, 2MB memory usage.

typedef struct {
    int prime_count;
    pthread_mutex_t lock;
} SharedData;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true; // 2 and 3 are prime
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false; // handle multiples of 2 and 3
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void* readAndCountPrimes(void* arg) {
    SharedData* data = (SharedData*) arg;
    int num;

    while (1) {
        // Lock for reading from stdin
        if (scanf("%d", &num) == EOF) {
            break;
        }
        // Check if the number is prime
        if (isPrime(num)) {
            // Lock to update shared prime count
            pthread_mutex_lock(&data->lock);
            data->prime_count++;
            pthread_mutex_unlock(&data->lock);
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_THREADS];
    pthread_attr_t attr;
    SharedData shared_data;
    shared_data.prime_count = 0;
    pthread_mutex_init(&shared_data.lock, NULL);

    // Initialize thread attribute
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, STACK_SIZE);

    // Start timing
    struct timespec start_time, end_time;
    if (clock_gettime(CLOCK_MONOTONIC, &start_time) != 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }

    // Create threads
    for (int i = 0; i < MAX_THREADS; i++) {
        int ret = pthread_create(&threads[i], &attr, readAndCountPrimes, (void*)&shared_data);
        if (ret != 0) {
            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // End timing
    if (clock_gettime(CLOCK_MONOTONIC, &end_time) != 0) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    double time_spent = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    

    printf("%d total primes.\n", shared_data.prime_count);
    printf("Time taken: %f seconds.\n", time_spent);
    // Print RAM usage
    // struct rusage usage;
    // getrusage(RUSAGE_SELF, &usage);
    // printf("Maximum resident set size (RAM usage): %ld KB\n", usage.ru_maxrss);
    // Clean up
    pthread_mutex_destroy(&shared_data.lock);

    return 0;
}
