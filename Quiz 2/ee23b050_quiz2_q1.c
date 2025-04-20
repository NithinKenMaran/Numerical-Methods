/*
    Name: Nithin Ken Maran
    Roll Number: EE23B050
    version 1.0
*/

/*
    *** referred the following sources ***
        ------------------------------

    1. use of clock() from tutorialspoint.com

                *** x *** x ***
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>



double total_t;
int main(int argc, char* argv[]) {

    clock_t start_t, end_t;
    
    start_t = clock(); //first call of clock() returns a starting timestamp
    
    long long N;
    long long R;
    long long a;
    long long b;
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen("ee23b050_quiz2_q1_output.txt", "w");

    fscanf(fin, "%lld %lld\n", &N, &R);

    long long* array = (long long*)malloc(N*sizeof(long long)); //allocates memory for array of N integers

    for (long long i = 0; i < N; i++) { //initializing array with element = index
        array[i] = i;
    }

    for (long long i = 0; i < R; i++) {
        fscanf(fin, "%lld %lld\n", &a, &b); //a->planet#1, b->planet#2

        if (array[a] == array[b]) { //a and b are already connected
            fprintf(fout, "%d", 0);
            continue;
        }
        for (long long j = 0; j < N; j ++ ) {
            if (array[j] == array[b]) { 
                //for every array element that is part of the same group
                //update them to be part of the new group
                array[j] = array[a];
                printf("hi\n");
                
            }

        }
        fprintf(fout, "%d", 1);

       
    }
    

    end_t = clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC; 
    //dividing by clockspersec, since clock() returns timestamp in ticks per second.
    fprintf(fout, "\n%f ms", (total_t*100));

    free(array);
    fclose(fin);
    fclose(fout);

    return 0;
}


