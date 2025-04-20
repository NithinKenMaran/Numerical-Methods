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
    3. use of typedef from geeksforgeeks.com

                *** x *** x ***
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct city {
    struct city *parent;
    long long value; 
    long long depth;
} city;

city *make(long long element);
city *find(city *element);
city *merge(city *a, city *b);

double total_t;
int main(int argc, char* argv[]) {

    clock_t start_t, end_t;
    start_t = clock();
    FILE *fout = fopen("ee23b050_quiz2_q3_output.txt", "w");
    FILE *fin = fopen(argv[1], "r");

    long long N, R;
    fscanf(fin, "%lld %lld\n", &N, &R);
    city *pointers[N]; // stores pointers to every planet

    for (long long i = 0; i < N; i++) {
        pointers[i] = make(i); // now, array contains unconnected planets
    }

    for (long long i = 0; i < R; i++) {
        long long a, b;
        fscanf(fin, "%lld %lld\n", &a, &b); // Read one road at a time

        if (find(pointers[a]) != find(pointers[b])) {
            // a and b aren't directly connected
            merge(pointers[a], pointers[b]);
            fprintf(fout, "%d", 1);
        } else {
            // a and b are already directly connected
            fprintf(fout, "%d", 0);
        }
    }

    fclose(fin);

    
    for (long long i = 0; i < N; i++) {
        free(pointers[i]);
    }

    
    end_t = clock();
    total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    fprintf(fout, "\n%.0f ms", ceil(total_t*1000));

    fclose(fout);
    return 0;

}

city *make(long long element) { //creates a single unconnected node
    city *single = (city *)malloc(sizeof(city));
    single->value = element;
    single->parent = NULL;
    single->depth = 1;
    return single;
}

city *find(city *element) {
    if (!element) { //when element doesn't exist
        return NULL;
    }

    if (element->parent != NULL) { //only the root would have parent = NULL
        element = element->parent; //traverse till root is reached.
    }

    return element;
}

city *merge(city *a, city *b) {
    city *root_a = find(a);
    city *root_b = find(b);
    city *newroot = root_a; 

    if (root_a != root_b) {
        if (root_a->depth < root_b->depth) {  //if b is deeper, b is made the parent
            root_a->parent = root_b;
            newroot = root_b;
        } else {  //if a is deeper, a is made the parent
            root_b->parent = root_a;
            if (root_a->depth == root_b->depth) {
                root_a->depth++;
            }
        }
    }

    return newroot;
}

