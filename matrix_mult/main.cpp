#include <iostream>
#include <omp.h>

#define SIZE 3 // Change this value for different matrix sizes

void matrixMultiplication(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE]) {
    #pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
            std::cout << "i = " << i << std::endl;
        for (int j = 0; j < SIZE; ++j) {
            result[i][j] = 0;
            std::cout << "j = " << j << std::endl;

            for (int k = 0; k < SIZE; ++k) {
                std::cout << "k = " << k << std::endl;
                result[i][j] += A[i][k] * B[k][j];
                std::cout << "Sample element of result matrix: " << result[i][j] << std::endl;
            }
        }
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], result[SIZE][SIZE];

    // Initialize matrices A and B (for the sake of demonstration, we'll use simple initialization)
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            std::cout << A[i][j] << std::endl;
            std::cout << B[i][j] << std::endl;
        }
    }

    double start_time = omp_get_wtime(); // Record start time

    matrixMultiplication(A, B, result);

    double end_time = omp_get_wtime(); // Record end time

    // Display execution time
    std::cout << "Matrix multiplication completed in " << end_time - start_time << " seconds." << std::endl;



}
