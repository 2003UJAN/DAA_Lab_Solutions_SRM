#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix
int** allocateMatrix(int rows, int cols) {
int i;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (i = 0; i < rows; i++)
        matrix[i] = (int*)malloc(cols * sizeof(int));
    return matrix;
}

// Function to free memory allocated to a matrix
void freeMatrix(int** matrix, int rows) {
int i;
    for (i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

// Function to add two matrices
int** addMatrices(int** A, int** B, int n) {
    int** result = allocateMatrix(n, n);
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Function to subtract two matrices
int** subtractMatrices(int** A, int** B, int n) {
    int** result = allocateMatrix(n, n);
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Function to print a matrix
void printMatrix(int** matrix, int rows, int cols) {
int i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to multiply two matrices using Strassen's algorithm
int** strassenMultiply(int** A, int** B, int n) {
int i,j;
    if (n == 1) {
        int** C = allocateMatrix(1, 1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    } else {
        // Allocate memory for result matrix
        int** C = allocateMatrix(n, n);

        // Splitting matrices into quadrants
        int new_size = n / 2;
        int** A11 = allocateMatrix(new_size, new_size);
        int** A12 = allocateMatrix(new_size, new_size);
        int** A21 = allocateMatrix(new_size, new_size);
        int** A22 = allocateMatrix(new_size, new_size);
        int** B11 = allocateMatrix(new_size, new_size);
        int** B12 = allocateMatrix(new_size, new_size);
        int** B21 = allocateMatrix(new_size, new_size);
        int** B22 = allocateMatrix(new_size, new_size);

        // Initialize quadrants
        for (i = 0; i < new_size; i++) {
            for (j = 0; j < new_size; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + new_size];
                A21[i][j] = A[i + new_size][j];
                A22[i][j] = A[i + new_size][j + new_size];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + new_size];
                B21[i][j] = B[i + new_size][j];
                B22[i][j] = B[i + new_size][j + new_size];
            }
        }

        // Calculating intermediate matrices
        int** P1 = strassenMultiply(A11, subtractMatrices(B12, B22, new_size), new_size);
        int** P2 = strassenMultiply(addMatrices(A11, A12, new_size), B22, new_size);
        int** P3 = strassenMultiply(addMatrices(A21, A22, new_size), B11, new_size);
        int** P4 = strassenMultiply(A22, subtractMatrices(B21, B11, new_size), new_size);
        int** P5 = strassenMultiply(addMatrices(A11, A22, new_size), addMatrices(B11, B22, new_size), new_size);
        int** P6 = strassenMultiply(subtractMatrices(A12, A22, new_size), addMatrices(B21, B22, new_size), new_size);
        int** P7 = strassenMultiply(subtractMatrices(A11, A21, new_size), addMatrices(B11, B12, new_size), new_size);

        // Calculating result matrix
        int** C11 = subtractMatrices(addMatrices(P5, P4, new_size), subtractMatrices(P2, P6, new_size), new_size);
        int** C12 = addMatrices(P1, P2, new_size);
        int** C21 = addMatrices(P3, P4, new_size);
        int** C22 = subtractMatrices(addMatrices(P5, P1, new_size), addMatrices(P3, P7, new_size), new_size);

        // Combining quadrants to form the result matrix
        for (i = 0; i < new_size; i++) {
            for (j = 0; j < new_size; j++) {
                C[i][j] = C11[i][j];
                C[i][j + new_size] = C12[i][j];
                C[i + new_size][j] = C21[i][j];
                C[i + new_size][j + new_size] = C22[i][j];
            }
        }

        // Free allocated memory
        freeMatrix(A11, new_size);
        freeMatrix(A12, new_size);
        freeMatrix(A21, new_size);
        freeMatrix(A22, new_size);
        freeMatrix(B11, new_size);
        freeMatrix(B12, new_size);
        freeMatrix(B21, new_size);
        freeMatrix(B22, new_size);
        freeMatrix(P1, new_size);
        freeMatrix(P2, new_size);
        freeMatrix(P3, new_size);
        freeMatrix(P4, new_size);
        freeMatrix(P5, new_size);
        freeMatrix(P6, new_size);
        freeMatrix(P7, new_size);
        freeMatrix(C11, new_size);
        freeMatrix(C12, new_size);
        freeMatrix(C21, new_size);
        freeMatrix(C22, new_size);

        return C;
    }
}

int main() {
    int n,i,j;
    printf("Enter the size of square matrices: ");
    scanf("%d", &n);

    // Allocate memory for matrices A and B
    int** A = allocateMatrix(n, n);
    int** B = allocateMatrix(n, n);

    // Input elements of matrix A
    printf("Enter elements of matrix A:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Input elements of matrix B
    printf("Enter elements of matrix B:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Multiply matrices using Strassen's algorithm
    int** result = strassenMultiply(A, B, n);

    // Print the result matrix
    printf("Result matrix:\n");
    printMatrix(result, n, n);

    // Free allocated memory
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(result, n);

    return 0;
}
