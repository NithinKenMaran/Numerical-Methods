/*
Name: Nithin Ken Maran
Roll No. : EE23B050
version: 1.0

***     description     ***

input: `./<program> <iteration limit> <r_increment> <error tolerance> `

*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>



int main(int argc, char **argv) {
    
    FILE *fout = fopen("plot.txt", "w");
    int iterlimit = atoi(argv[1]);
    float tolerance = atof(argv[3]);
    float r_inc = atof(argv[2]);
    float r = 0;
    float error = 100;

    while (r <= 4) {
        float xold = 0.5; 
        for (int i = 0; i < iterlimit; i++) {

            if (error < 
            float xnew = r * xold * (1 - xold);
            error = fabs((xnew - xold) * 100 / xnew);
            fprintf(fout, "%f   %f\n", r, xnew);
            xold = xnew;  
        }
        r += r_inc; 
    }

    fclose(fout);
    return 0;
}
