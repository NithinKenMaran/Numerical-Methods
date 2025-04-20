/*
Name: Nithin Ken Maran
rollnumber: EE23B050


*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

int N;
float Nseed;
int M;
float Mseed;
int minham = 0;
int minham_index = 0; // To store the index where the minimum Hamming distance is found

int* nbits;
int* mbits;

int main(int argc, char* argv[]) {
    FILE* nfile = fopen("Nfile.dat", "w");
    FILE* mfile = fopen("Mfile.dat", "w");

    N = atoi(argv[1]);
    Nseed = atof(argv[2]);
    M = atoi(argv[3]);
    Mseed = atof(argv[4]);

    if (M > N) {
        printf("Enter M, N such that M < N\n");
        exit(0);
    }

    nbits = (int*)malloc(N * sizeof(int));
    mbits = (int*)malloc(M * sizeof(int));

    srand((unsigned)Nseed);
    for (int i = 0; i < N; i++) {
        nbits[i] = rand() % 2;
    }

    srand((unsigned)Mseed);
    for (int i = 0; i < M; i++) {
        mbits[i] = rand() % 2;
    }

    // Printing nbits and mbits into their respective files
    for (int i = 0; i < N; i++) {
        fprintf(nfile, "%d ", nbits[i]);
    }
    fclose(nfile);

    for (int i = 0; i < M; i++) {
        fprintf(mfile, "%d ", mbits[i]);
    }
    fclose(mfile);

    int* nbitsptr = nbits;
    int* mbitsptr = mbits;

    for (int i = 0; i <= N - M; i++) {
        int minham_current = 0;
        for (int j = 0; j < M; j++) {
            if (*mbitsptr != *nbitsptr) {
                minham_current++;
            }
            mbitsptr++;
            nbitsptr++;
        }

        if (i == 0 || minham_current < minham) { 
        // "||" indicates "or" operator (found
            minham = minham_current;
            minham_index = i; // Update the index where the minimum Hamming distance is found
        }
        nbitsptr = nbits + i + 1;
        mbitsptr = mbits;
    }

    printf("%d %d", minham, minham_index);


    free(nbits);
    free(mbits);

    return 0;
}
