/*
    Name: Nithin Ken Maran
    Roll Number: EE23B050
    version 1.0
*/

/*
    *** referred to the following sources ***
        ---------------------------------

    1. use of clock() from tutorialspoint.com
    2. Union-Find algorithm from geeksforgeeks.com and hackerearth.com

                *** x *** x ***
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int find(long long*, long long);
int merge(long long*, long long*, long long, long long, FILE*);

double total_t;
int main(int argc, char* argv[]) {

    clock_t start_t, end_t;
    start_t = clock();

    FILE * fin = fopen(argv[1], "r");
    FILE * fout = fopen("ee23b050_quiz2_q4_output.txt", "w");

    long long N,R;
    fscanf(fin, "%lld %lld\n", &N, &R);
    long long * parents = (long long*)malloc(N*sizeof(long long)); 
    long long * depths = (long long*)malloc(N*sizeof(long long));

    for (long long i = 0; i<N; i++) { //initializing array with element = index
        parents[i] = i;
        depths[i] = 1;

    }

    for (long long i = 0; i < R; i++) {

        long long a,b;
        fscanf(fin, "%lld %lld\n", &a, &b);
        merge(parents, depths, a, b, fout);

    }
    free(parents);
    free(depths);
    fclose(fin);

    end_t = clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    fprintf(fout, "\n%.0f ms", ceil(total_t*1000));

    fclose(fout);
    return 0;
    
}

int find(long long * parents, long long element) { 
    //compresses path, cuz at the end of this process, the element's parent would point directly to the root instead of through a long chain of nodes
    
    while (element != parents[element]) {

        element = parents[element];

    }

    return element;
    
}

int merge(long long *parents, long long *depths, long long a, long long b, FILE* fout) {
    long long root_a = find(parents, a);
    long long root_b = find(parents, b);

    if (root_a == root_b) {
        // a and b are already in the same set
        fprintf(fout, "%d", 0);
    } else {
        
        if (depths[root_a] < depths[root_b]) { //when b is deeper, it becomes the parent
            parents[root_a] = root_b;
            fprintf(fout, "%d", 1);
            depths[root_a]++;
        } else if (depths[root_a] > depths[root_b]) { //when a is deeper, it becomes the parent
            parents[root_b] = root_a;
            fprintf(fout, "%d", 1);
            depths[root_b]++;
        } else {
            // Both sets have the same depth, choose one as the parent
            parents[root_b] = root_a;
            depths[root_b]++;
            fprintf(fout, "%d", 1);
        }
    }

    return 0;
}
