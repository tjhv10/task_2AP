# Prime Counter 

## Instructions

1. **Compile the programs**:
    ```sh
    make
    ```

2. **Run the tests and capture outputs**:
    ```sh
    ./run.sh
    ```

3. ## Results

    ### Reference Prime Counter
    
    ![Reference Output](screenshots/reference_output.png)
    ![Reference Memory](screenshots/reference_memory.png)
    
    ### Optimized Prime Counter
    
    ![Optimized Output](screenshots/optimized_output.png)
    ![Optimized Memory](screenshots/optimized_memory.png)

5. **Clean up**:
    ```sh
    make clean
    ```

## Explanation

- The `randomGenerator` generates a stream of random numbers.
- The `newPrimeCounter` uses multithreading to count the number of prime numbers in the stream efficiently.
