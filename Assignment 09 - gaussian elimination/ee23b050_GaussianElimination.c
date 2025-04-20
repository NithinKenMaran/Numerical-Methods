/* 
Collaborators : - Nithin Ken Maran (EE23B050)
                - Rohita Datta (EE23B065)

Inputs : Filename, N
Output : N values of x
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
//code to implement Gauss Elimination with elimination, back substitution and pivoting to solve a system of equations

// Function to initialize the coefficient matrix 'a' and constants array 'b'
void initialise(float **a, float *b, int N, FILE *file);

// Function to perform Gaussian Elimination with partial pivoting
void Gauss(float **a, float *b, int N, int *er, float tol);

// Function to perform back substitution to find the solution
void Substitute(float **a, float *b, int N, float *x);

// Function to perform row pivoting
void pivot(float **a, float *b, int N, int row);

// Function used in LU decomposition
void Eliminate(float **a, float *b, int N, int row);

int main(int argc, char* argv[]){
//take inputs 
    char* fname = argv[1];
    FILE* file = fopen(fname, "r");
    int N = atoi(argv[2]);
    
    float **a = malloc(N * sizeof(float *));
    for(int i = 0; i < N; i++)
        a[i] = malloc(N * sizeof(float));
    float *b = malloc(N * sizeof(float));
    float *x = malloc(N * sizeof(float));
    initialise(a, b, N, file);
    int er = 0; // Error variable
    float tol = 0.0000001; // Tolerance
    Gauss(a, b, N, &er, tol);
    Substitute(a, b, N, x);
    
    for(int i = 0; i < N; i++){
        printf("%f\n", x[i]);
    }
    
    // Clean up allocated memory
    for(int i = 0; i < N; i++)
        free(a[i]);
    free(a);
    free(b);
    free(x);

    fclose(file);

    return 0;
}

void initialise(float **a, float *b, int N, FILE *file){
    // Reading coefficients 'a' and constants 'b' from the input file
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            fscanf(file, "%f", &a[i][j]);
        }
        fscanf(file, "%f", &b[i]);
    }
}

void Gauss(float **a, float *b, int N, int *er, float tol){
    for (int i = 0; i < N; i++) {
        pivot(a, b, N, i);
        for (int j = i+1; j < N; j++) {
            float factor = a[j][i] / a[i][i];
            for (int k = i; k < N; k++) {
                a[j][k] -= factor * a[i][k];
            }
            b[j] -= factor * b[i];
        }
        if (fabs(a[i][i]) < tol) {
            *er = -1; // Set error flag if division by zero may occur
            printf("no solutions");
            return; // Exit function if division by zero may occur
        }
    }
}

void Substitute(float **a, float *b, int N, float *x) {
    for (int i = N - 1; i >= 0; i--) {
        float sum = 0;
        for (int j = i + 1; j < N; j++) {
            sum += a[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / a[i][i];
    }
}

void pivot(float **a, float *b, int N, int row) {
    int p = row;
    for (int i = row+1; i < N; i++) {
        if (fabs(a[i][row]) > fabs(a[p][row])) {
            p = i;
        }
    }

    // Swap rows in 'a' and elements in 'b'
    float *temp = a[row];
    a[row] = a[p];
    a[p] = temp;
    float temp_b = b[row];
    b[row] = b[p];
    b[p] = temp_b;
}

void Eliminate(float **a, float *b, int N, int row) {
    // This function is included for completeness, but it's not actively used in Gaussian Elimination with partial pivoting.
    // It's typically used in LU decomposition.
    for (int i = row+1; i < N; i++) {
        float factor = a[i][row] / a[row][row];
        for (int j = row; j < N; j++) {
            a[i][j] -= factor * a[row][j];
        }
        b[i] -= factor * b[row];
    }
}